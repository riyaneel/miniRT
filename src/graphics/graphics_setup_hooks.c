/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_setup_hooks.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:05:45 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/11 20:52:40 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics/graphics.h"

static int	on_window_close(void *param)
{
	t_graphics	*gfx;

	gfx = (t_graphics *)param;
	if (gfx && gfx->mlx)
		mlx_loop_end(gfx->mlx);
	return (0);
}

static int	on_keypress(const int keysim, void *param)
{
	t_graphics	*gfx;

	gfx = (t_graphics *)param;
	if (keysim == XK_Escape)
		mlx_loop_end(gfx->mlx);
	return (0);
}

static int	on_render_loop(void *param)
{
	t_graphics	*gfx;

	gfx = (t_graphics *)param;
	graphics_clear(gfx);
	// todo: add raytracing in future
	graphics_present(gfx);
	return (0);
}

void	graphics_setup_hooks(t_graphics *gfx)
{
	if (!gfx || !gfx->win)
		return ;
	mlx_hook(gfx->win, DestroyNotify, 0, on_window_close, gfx);
	mlx_hook(gfx->win, KeyPress, KeyPressMask, on_keypress, gfx);
	mlx_loop_hook(gfx->mlx, on_render_loop, gfx);
}
