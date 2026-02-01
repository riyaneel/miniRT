/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 03:47:03 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/19 01:45:46 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "raytracer/camera.h"
#include "raytracer/render.h"
#include "utils/maths_utils.h"

static void	render_line_local(const t_render_ctx *ctx, t_vec4 *line_buffer,
		const int y, int x, const int limit_x)
{
	int	local_x;

	local_x = 0;
	while (x < limit_x)
	{
		line_buffer[local_x] = render_pixel(ctx->gfx->scene, x, y, 1);
		x++;
		local_x++;
	}
}

static void	render_tile(const t_render_ctx *ctx, const int tile_idx)
{
	t_vec4	local_buffer[RT_TILE_SIZE * RT_TILE_SIZE];
	int		x_start;
	int		y_start;
	int		y;
	int		lim_x;
	int		lim_y;
	int		w_span;
	int		fb_idx;
	int		local_idx;

	x_start = (tile_idx % ctx->tiles_x) * RT_TILE_SIZE;
	y_start = (tile_idx / ctx->tiles_x) * RT_TILE_SIZE;
	lim_x = (int)fmin_fast((float)x_start + RT_TILE_SIZE, (float)ctx->gfx->width);
	lim_y = (int)fmin_fast((float)y_start + RT_TILE_SIZE, (float)ctx->gfx->height);
	w_span = lim_x - x_start;
	y = y_start;
	local_idx = 0;
	while (y < lim_y)
	{
		render_line_local(ctx, &local_buffer[local_idx], y, x_start, lim_x);
		local_idx += w_span;
		y++;
	}
	y = y_start;
	local_idx = 0;
	while (y < lim_y)
	{
		fb_idx = y * ctx->gfx->width + x_start;
		__builtin_memcpy(&ctx->gfx->framebuffer->pixels[fb_idx],
			&local_buffer[local_idx], (size_t)w_span * sizeof(t_vec4));
		local_idx += w_span;
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
