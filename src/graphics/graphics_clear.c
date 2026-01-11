/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_clear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:05:31 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/11 20:51:35 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics/graphics.h"

void	graphics_clear(t_graphics *gfx)
{
	if (!gfx || !gfx->framebuffer || !gfx->framebuffer->pixels)
		return ;
	__builtin_memset(gfx->framebuffer->pixels, 0, gfx->framebuffer->size_bytes);
}
