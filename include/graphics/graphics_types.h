/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_types.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 19:38:06 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/11 19:48:13 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_TYPES_H
# define GRAPHICS_TYPES_H

# include "mlx.h"

# include "vectors/vector_types.h"

typedef struct s_framebuffer {
	int		width;
	int		height;
	t_vec4	*pixels;
	size_t	size_bytes;
}	t_framebuffer;

typedef struct s_graphics {
	t_mlx			*mlx;
	t_window		*win;
	t_framebuffer	*framebuffer;
	int				width;
	int				height;
}	t_graphics;

#endif // GRAPHICS_TYPES_H
