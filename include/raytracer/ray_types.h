/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:27:39 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 17:16:58 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_TYPES_H
# define RAY_TYPES_H

# include <stdbool.h>
# include <stdint.h>

# include "vectors/vector_types.h"

typedef struct s_ray {
	t_vec4	origin;
	t_vec4	dir;
}	t_ray;

typedef enum e_hit_type {
	HIT_NONE = 0,
	HIT_SPHERE = 1,
	HIT_PLANE = 2,
	HIT_CYLINDER = 3,
	HIT_MESH = 4,
}	t_hit_type;

typedef struct s_hit_record {
	t_vec4		p;
	t_vec4		normal;
	t_vec4		color_obj;
	t_vec4		obj_center;
	t_vec4		obj_axis;
	float		t;
	t_hit_type	type;
	bool		front_face;
	uint8_t		padding[7];
}	t_hit;

#endif // RAY_TYPES_H
