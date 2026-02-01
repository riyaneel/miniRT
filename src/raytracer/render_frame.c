/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 03:47:03 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 16:07:32 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "raytracer/camera.h"
#include "raytracer/render.h"

static void	init_ctx(t_render_ctx *ctx, t_graphics *gfx)
{
	ctx->gfx = gfx;
	ctx->next_tile = 0;
	ctx->tiles_x = (gfx->width + RT_TILE_SIZE - 1) / RT_TILE_SIZE;
	ctx->tiles_y = (gfx->height + RT_TILE_SIZE - 1) / RT_TILE_SIZE;
	ctx->total_tiles = ctx->tiles_x * ctx->tiles_y;
}

static t_thread_data	*alloc_thread_data(t_render_ctx *ctx, const int n)
{
	t_thread_data	*data;
	int				i;
	size_t			buf_size;

	data = malloc(sizeof(t_thread_data) * (size_t)n);
	if (!data)
		return (NULL);
	buf_size = RT_TILE_SIZE * RT_TILE_SIZE * sizeof(t_vec4);
	i = 0;
	while (i < n)
	{
		data[i].ctx = ctx;
		data[i].buffer = malloc(buf_size);
		if (!data[i].buffer)
			return (free_thread_data(data, i), NULL);
		i++;
	}
	return (data);
}

void	render_frame(t_graphics *gfx)
{
	t_render_ctx	ctx;
	t_thread_data	*data;
	pthread_t		*th;
	int				n;

	n = (int)sysconf(_SC_NPROCESSORS_ONLN);
	if (n < 1)
		n = 1;
	th = malloc(sizeof(pthread_t) * (size_t)n);
	if (!th)
		return ;
	init_ctx(&ctx, gfx);
	data = alloc_thread_data(&ctx, n);
	if (!data)
	{
		free(th);
		return ;
	}
	camera_init_viewport(&gfx->scene->camera, gfx->width, gfx->height);
	spawn_threads(th, data, n);
	join_threads(th, data, n);
	free(th);
}
