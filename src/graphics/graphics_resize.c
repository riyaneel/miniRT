/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_resize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 18:22:03 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 18:26:54 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics/graphics.h"

__attribute__((always_inline))
static inline int	clamp_int(const int value, const int min_val,
		const int max_val)
{
	if (value < min_val)
		return (min_val);
	if (value > max_val)
		return (max_val);
	return (value);
}

void	graphics_resize(t_graphics *gfx, int new_width, int new_height)
{
	if (!gfx || !gfx->framebuffer)
		return ;
	new_width = clamp_int(new_width, 64, gfx->framebuffer->max_width);
	new_height = clamp_int(new_height, 64, gfx->framebuffer->max_height);
	if (new_width == gfx->width && new_height == gfx->height)
		return ;
	gfx->width = new_width;
	gfx->height = new_height;
	gfx->framebuffer->width = new_width;
	gfx->framebuffer->height = new_height;
	gfx->needs_render = true;
}
