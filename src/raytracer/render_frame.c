/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 03:47:03 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/19 01:17:48 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "raytracer/camera.h"
#include "raytracer/render.h"
#include "utils/maths_utils.h"

static void	render_line(const t_render_ctx *ctx, const int y, int x,
		const int limit_x)
{
	int	idx;

	while (x < limit_x)
	{
		idx = y * ctx->gfx->width + x;
		ctx->gfx->framebuffer->pixels[idx] = \
			render_pixel(ctx->gfx->scene, x, y, 1);
		x++;
	}
}

static void	render_tile(const t_render_ctx *ctx, const int tile_idx)
{
	int	x;
	int	y;
	int	lim_x;
	int	lim_y;

	x = (tile_idx % ctx->tiles_x) * RT_TILE_SIZE;
	y = (tile_idx / ctx->tiles_x) * RT_TILE_SIZE;
	lim_x = (int)fmin_fast((float)x + RT_TILE_SIZE, (float)ctx->gfx->width);
	lim_y = (int)fmin_fast((float)y + RT_TILE_SIZE, (float)ctx->gfx->height);
	while (y < lim_y)
	{
		render_line(ctx, y, x, lim_x);
		y++;
	}
}

static void	*thread_routine(void *arg)
{
	t_render_ctx	*ctx;
	int				tile_idx;

	ctx = (t_render_ctx *)arg;
	while (1)
	{
		tile_idx = __atomic_fetch_add(&ctx->next_tile, 1, __ATOMIC_RELAXED);
		if (tile_idx >= ctx->total_tiles)
			break ;
		render_tile(ctx, tile_idx);
	}
	return (NULL);
}

static void	init_ctx(t_render_ctx *ctx, t_graphics *gfx)
{
	ctx->gfx = gfx;
	ctx->next_tile = 0;
	ctx->tiles_x = (gfx->width + RT_TILE_SIZE - 1) / RT_TILE_SIZE;
	ctx->tiles_y = (gfx->height + RT_TILE_SIZE - 1) / RT_TILE_SIZE;
	ctx->total_tiles = ctx->tiles_x * ctx->tiles_y;
}

__attribute__((noinline))
void	render_frame(t_graphics *gfx)
{
	t_render_ctx	ctx;
	pthread_t		*th;
	long			n;
	int				i;

	n = sysconf(_SC_NPROCESSORS_ONLN);
	if (n < 1)
		n = 1;
	th = malloc(sizeof(pthread_t) * (size_t)n);
	if (!th)
		return ;
	init_ctx(&ctx, gfx);
	camera_init_viewport(&gfx->scene->camera, gfx->width, gfx->height);
	i = -1;
	while (++i < n)
		if (pthread_create(&th[i], NULL, thread_routine, &ctx) != 0)
			break ;
	while (--i >= 0)
		pthread_join(th[i], NULL);
	free(th);
}
