/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:41:25 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/11 22:41:18 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_TYPES_H
# define SCENE_TYPES_H

# include <stdbool.h>

# include "vectors/vector_types.h"

typedef struct s_sphere {
	t_vec4	center;
	t_vec4	color;
	float	radius;
	float	padding[3];
}	t_sphere;

typedef struct s_plane {
	t_vec4	point;
	t_vec4	normal;
	t_vec4	color;
}	t_plane;

typedef struct s_cylinder {
	t_vec4	center;
	t_vec4	axis;
	t_vec4	color;
	float	radius;
	float	height;
	float	padding[2];
}	t_cylinder;

typedef struct s_ambient {
	t_vec4	color;
	float	ratio;
	float	padding[3];
}	t_ambient;

typedef struct s_camera {
	t_vec4	origin;
	t_vec4	dir;
	float	fov;
	float	aspect_ratio;
	char	padding[8];
	t_vec4	viewport_u;
	t_vec4	viewport_y;
	t_vec4	pixel_00_loc;
}	t_camera;

typedef struct s_light {
	t_vec4	origin;
	t_vec4	color;
	float	ratio;
	float	padding[3];
}	t_light;

typedef struct s_scene {
	t_sphere	*spheres;
	t_plane		*planes;
	t_cylinder	*cylinders;
	int			num_spheres;
	int			num_planes;
	int			num_cylinders;
	bool		has_cam;
	bool		has_amb;
	bool		has_light;
	char		reserved[9];
	t_camera	camera;
	t_ambient	ambient;
	t_light		light;
}	t_scene;

#endif // SCENE_TYPES_H
