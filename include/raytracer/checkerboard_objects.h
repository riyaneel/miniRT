/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard_objects.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 17:22:54 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 17:54:29 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKERBOARD_OBJECTS_H
# define CHECKERBOARD_OBJECTS_H

# include "checkerboard_types.h"
# include "checkerboard_utils.h"
# include "ray_types.h"
# include "vectors/rt_vectors.h"

static inline t_vec4	checker_plane(const t_hit *rec)
{
	int	check;

	check = checker_pattern(rec->p.x, rec->p.z, CHECKER_SCALE);
	return (checker_blend(rec->color_obj, check));
}

static inline t_vec4	checker_sphere(const t_hit *rec)
{
	t_vec4	local;
	float	u;
	float	v;
	int		check;

	local = vec4_normalize(vec4_sub(rec->p, rec->obj_center));
	u = (atan2f(local.x, local.z) + (float)M_PI) / (2.0f * (float)M_PI);
	v = (asinf(local.y) + (float)M_PI_2) / (float)M_PI;
	check = checker_pattern(u, v, CHECKER_SCALE_SPH);
	return (checker_blend(rec->color_obj, check));
}

static inline t_vec4	build_tangent(const t_vec4 axis)
{
	t_vec4	up;
	t_vec4	tangent;

	if (fabsf(axis.y) < 0.999f)
		up = (t_vec4){{0.0f, 1.0f, 0.0f, 0.0f}};
	else
		up = (t_vec4){{1.0f, 0.0f, 0.0f, 0.0f}};
	tangent = vec4_cross(axis, up);
	return (vec4_normalize(tangent));
}

static inline t_vec4	checker_cylinder(const t_hit *rec)
{
	t_vec4	local;
	t_vec4	tangent;
	t_vec4	bitangent;
	float	h;
	float	u;

	local = vec4_sub(rec->p, rec->obj_center);
	h = vec4_dot(local, rec->obj_axis);
	tangent = build_tangent(rec->obj_axis);
	bitangent = vec4_cross(rec->obj_axis, tangent);
	u = atan2f(vec4_dot(local, bitangent), vec4_dot(local, tangent));
	u = (u + (float)M_PI) / (2.0f * (float)M_PI);
	return (checker_blend(rec->color_obj,
			checker_pattern(u, h, CHECKER_SCALE_CYL)));
}

#endif // CHECKERBOARD_OBJECTS_H
