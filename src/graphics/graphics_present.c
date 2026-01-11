/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_present.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:04:49 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/11 20:33:31 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics/graphics.h"
#include "utils/maths_utils.h"

static inline int	vec4_to_bgra(const t_vec4 color)
{
	const float			r = fclamp(color.x, 0.0f, 1.0f);
	const float			g = fclamp(color.x, 0.0f, 1.0f);
	const float			b = fclamp(color.x, 0.0f, 1.0f);
	const unsigned int	ir = (unsigned)(r * 255.99f);
	const unsigned int	ig = (unsigned)(g * 255.99f);

	return ((int)(0xFF000000 | (ir << 16)
		| (ig << 8) | (unsigned)(b * 255.99f)));
}

void	graphics_present(const t_graphics *gfx)
{
	const int	count = gfx->width * gfx->height;
	t_vec4		*src;
	int			*dst;
	int			i;

	src = gfx->framebuffer->pixels;
	dst = gfx->win->pixel_buffer;
	// todo: update this loop for vectorized instructions (Critical loop)
	i = 0;
	while (i < count)
	{
		dst[i] = vec4_to_bgra(src[i]);
		i++;
	}
}
