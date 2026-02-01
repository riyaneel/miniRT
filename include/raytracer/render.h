/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 03:46:13 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 16:07:53 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "graphics/graphics.h"

# define RT_TILE_SIZE	32

typedef struct s_render_ctx
{
	t_graphics	*gfx;
	int			next_tile;
	int			tiles_x;
	int			tiles_y;
	int			total_tiles;
}	t_render_ctx;

typedef struct s_thread_data
{
	t_render_ctx	*ctx;
	t_vec4			*buffer;
}	t_thread_data;

typedef struct s_tile_data
{
	int		x_start;
	int		y_start;
	int		lim_x;
	int		lim_y;
	int		w_span;
	uint8_t	padding[12];
}	t_tile_data;

void	render_frame(t_graphics *gfx);

void	render_tile(const t_render_ctx *ctx, int tile_idx, t_vec4 *buffer);

void	*thread_routine(void *arg);

void	free_thread_data(t_thread_data *data, int count);

void	spawn_threads(pthread_t *th, t_thread_data *data, int n);

void	join_threads(const pthread_t *th, t_thread_data *data, int n);

t_vec4	render_pixel(const t_scene *scn, int x, int y, uint32_t seed);

#endif // RENDER_H
