/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_types.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:41:25 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 18:02:17 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_TYPES_H
# define SCENE_TYPES_H

# include <stdbool.h>

# include "mesh_types.h"
# include "vectors/vector_types.h"

typedef struct s_sphere {
	float	*x;
	float	*y;
	float	*z;
	float	*r_sq;
	float	*inv_r;
	t_vec4	*colors;
	int		count;
	uint8_t	padding[12];
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

typedef struct s_cone {
	t_vec4	apex;
	t_vec4	axis;
	t_vec4	color;
	float	tan2;
	float	height;
	float	radius;
	float	padding;
}	t_cone;

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
	t_sphere	spheres;
	t_plane		*planes;
	t_cylinder	*cylinders;
	t_cone		*cones;
	t_mesh		*meshes;
	t_light		*lights;
	int			num_planes;
	int			num_cylinders;
	int			num_cones;
	int			num_meshes;
	int			num_lights;
	bool		has_cam;
	bool		has_amb;
	uint8_t		padding[2];
	t_camera	camera;
	t_ambient	ambient;
}	t_scene;

#endif // SCENE_TYPES_H
