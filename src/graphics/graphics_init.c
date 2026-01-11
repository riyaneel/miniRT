/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 19:39:08 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/11 19:55:03 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/arena_allocator.h"
#include "graphics/graphics.h"

static t_framebuffer	*framebuffer_init(t_arena *arena, const int width,
		const int height)
{
	t_framebuffer	*framebuffer;

	framebuffer = arena_alloc(arena, sizeof(t_framebuffer));
	if (!framebuffer)
		return (NULL);
	framebuffer->width = width;
	framebuffer->height = height;
	framebuffer->size_bytes = (size_t)(width * height) * sizeof(t_vec4);
	framebuffer->pixels = arena_alloc_align(arena, framebuffer->size_bytes, 16);
	return (framebuffer);
}

bool	graphics_init(t_graphics *gfx, t_arena *arena, const int w, const int h)
{
	gfx->width = w;
	gfx->height = h;
	gfx->mlx = mlx_init();
	if (!gfx->mlx)
		return (false);
	gfx->win = mlx_new_window(gfx->mlx, w, h, "MiniRt");
	if (!gfx->win)
	{
		mlx_destroy_display(gfx->mlx);
		return (false);
	}
	gfx->framebuffer = framebuffer_init(arena, w, h);
	if (!gfx->framebuffer)
	{
		graphics_shutdown(gfx);
		return (false);
	}
	return (true);
}
