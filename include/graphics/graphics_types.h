/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_types.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 19:38:06 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 18:20:45 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_TYPES_H
# define GRAPHICS_TYPES_H

# include "mlx.h"

# include "vectors/vector_types.h"

# define MAX_WIDTH 3840
# define MAX_HEIGHT 2160

typedef struct s_scene	t_scene;

typedef struct s_framebuffer {
	int		width;
	int		height;
	int		max_width;
	int		max_height;
	t_vec4	*pixels;
	size_t	size_bytes;
}	t_framebuffer;

typedef struct s_graphics {
	t_mlx			*mlx;
	t_window		*win;
	t_framebuffer	*framebuffer;
	int				width;
	int				height;
	bool			needs_render;
	uint8_t			padding[7];
	t_scene			*scene;
}	t_graphics;

#endif // GRAPHICS_TYPES_H
