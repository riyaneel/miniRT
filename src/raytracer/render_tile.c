/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_tile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 13:32:37 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 16:09:26 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer/render.h"
#include "utils/maths_utils.h"

static void	init_tile_data(t_tile_data *tile, const t_render_ctx *ctx,
		const int tile_idx)
{
	int	max_x;
	int	max_y;

	tile->x_start = (tile_idx % ctx->tiles_x) * RT_TILE_SIZE;
	tile->y_start = (tile_idx / ctx->tiles_x) * RT_TILE_SIZE;
	max_x = tile->x_start + RT_TILE_SIZE;
	max_y = tile->y_start + RT_TILE_SIZE;
	tile->lim_x = (int)fmin_fast((float)max_x, (float)ctx->gfx->width);
	tile->lim_y = (int)fmin_fast((float)max_y, (float)ctx->gfx->height);
	tile->w_span = tile->lim_x - tile->x_start;
}

static void	render_tile_lines(const t_render_ctx *ctx, const t_tile_data *tile,
		t_vec4 *buffer)
{
	int	y;
	int	x;
	int	idx;

	y = tile->y_start;
	idx = 0;
	while (y < tile->lim_y)
	{
		x = tile->x_start;
		while (x < tile->lim_x)
		{
			buffer[idx++] = render_pixel(ctx->gfx->scene, x, y, 1);
			x++;
		}
		y++;
	}
}

static void	copy_tile_to_fb(const t_render_ctx *ctx, const t_tile_data *tile,
		const t_vec4 *buffer)
{
	int		y;
	int		idx;
	int		fb_idx;
	size_t	row_size;

	y = tile->y_start;
	idx = 0;
	row_size = (size_t)tile->w_span * sizeof(t_vec4);
	while (y < tile->lim_y)
	{
		fb_idx = y * ctx->gfx->width + tile->x_start;
		__builtin_memcpy(&ctx->gfx->framebuffer->pixels[fb_idx],
			&buffer[idx], row_size);
		idx += tile->w_span;
		y++;
	}
}

void	render_tile(const t_render_ctx *ctx, const int tile_idx, t_vec4 *buffer)
{
	t_tile_data	tile;

	init_tile_data(&tile, ctx, tile_idx);
	render_tile_lines(ctx, &tile, buffer);
	copy_tile_to_fb(ctx, &tile, buffer);
}
