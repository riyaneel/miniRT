/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 03:46:13 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/19 01:17:28 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "graphics/graphics.h"

# define RT_TILE_SIZE	64

typedef struct s_render_ctx {
	t_graphics		*gfx;
	int				next_tile;
	int				total_tiles;
	int				tiles_x;
	int				tiles_y;
}	t_render_ctx;

void	render_frame(t_graphics *gfx);

t_vec4	render_pixel(const t_scene *scn, int x, int y, uint32_t seed);

#endif // RENDER_H
