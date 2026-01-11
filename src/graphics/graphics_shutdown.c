/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_shutdown.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 19:39:54 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/11 20:43:28 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "graphics/graphics.h"

void	graphics_shutdown(t_graphics *gfx)
{
	if (gfx->win)
		mlx_destroy_window(gfx->mlx, gfx->win);
	if (gfx->mlx)
	{
		mlx_destroy_display(gfx->mlx);
		free(gfx->mlx);
		gfx->mlx = NULL;
	}
}
