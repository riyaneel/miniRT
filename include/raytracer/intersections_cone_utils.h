/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_cone_utils.h                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 18:08:15 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 18:18:34 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTIONS_CONE_UTILS_H
# define INTERSECTIONS_CONE_UTILS_H

# include <math.h>

# include "ray.h"
# include "scene/scene_types.h"

typedef struct s_cone_eq
{
	t_vec4	oc;
	float	a;
	float	half_b;
	float	c;
	float	disc;
	float	dot_dv;
	float	dot_ocv;
	uint8_t	padding[8];
}	t_cone_eq;

static inline bool	init_cone_eq(const t_cone *co, const t_ray *r,
		t_cone_eq *eq)
{
	float	k;

	eq->oc = vec4_sub(r->origin, co->apex);
	eq->dot_dv = vec4_dot(r->dir, co->axis);
	eq->dot_ocv = vec4_dot(eq->oc, co->axis);
	k = 1.0f + co->tan2;
	eq->a = vec4_dot(r->dir, r->dir) - k * eq->dot_dv * eq->dot_dv;
	eq->half_b = vec4_dot(eq->oc, r->dir) - k * eq->dot_ocv * eq->dot_dv;
	eq->c = vec4_dot(eq->oc, eq->oc) - k * eq->dot_ocv * eq->dot_ocv;
	eq->disc = eq->half_b * eq->half_b - eq->a * eq->c;
	return (eq->disc >= 0.0f);
}

static inline bool	check_cone_root(const t_cone *co, const t_ray *r,
		const t_cone_eq *eq, t_hit *rec)
{
	float	m;
	t_vec4	p_on_axis;
	t_vec4	normal;

	if (rec->t <= EPSILON)
		return (false);
	m = eq->dot_dv * rec->t + eq->dot_ocv;
	if (m < 0.0f || m > co->height)
		return (false);
	rec->p = ray_at(r, rec->t);
	p_on_axis = vec4_add(co->apex, vec4_scale(co->axis, m));
	normal = vec4_sub(rec->p, p_on_axis);
	normal = vec4_normalize(normal);
	normal = vec4_sub(normal, vec4_scale(co->axis, sqrtf(co->tan2)));
	hit_set_face_normal(rec, r, vec4_normalize(normal));
	return (true);
}

static inline bool	check_cone_cap(const t_ray *ray, const t_cone *co,
		t_hit *rec, const float t_max)
{
	float	denom;
	float	t;
	t_vec4	cap_center;
	t_vec4	p;

	denom = vec4_dot(ray->dir, co->axis);
	if (fabsf(denom) < EPSILON)
		return (false);
	cap_center = vec4_add(co->apex, vec4_scale(co->axis, co->height));
	t = vec4_dot(vec4_sub(cap_center, ray->origin), co->axis) / denom;
	if (t < EPSILON || t > t_max)
		return (false);
	p = ray_at(ray, t);
	if (vec4_len_sq(vec4_sub(p, cap_center)) > co->radius * co->radius)
		return (false);
	rec->t = t;
	rec->p = p;
	hit_set_face_normal(rec, ray, co->axis);
	return (true);
}

#endif // INTERSECTIONS_CONE_UTILS_H
