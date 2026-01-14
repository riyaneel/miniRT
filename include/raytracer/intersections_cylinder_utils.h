/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_cylinder_utils.h                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 03:25:19 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/14 16:37:43 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTIONS_CYLINDER_UTILS_H
# define INTERSECTIONS_CYLINDER_UTILS_H

# include <math.h>
# include "ray.h"
# include "scene/scene_types.h"

typedef struct s_cap_data {
	t_vec4	center;
	t_vec4	normal;
	float	radius;
	float	t_max;
	char	padding[8];
}	t_cap_data;

typedef struct s_cy_eq {
	t_vec4	oc;
	float	a;
	float	half_b;
	float	c;
	float	disc;
	float	dot_dv;
	float	dot_ocv;
	char	padding[8];
}	t_cy_eq;

static inline bool	check_cap(const t_ray *ray, t_hit *rec,
		const t_cap_data *d)
{
	float	denom;
	float	t;
	t_vec4	p;

	denom = vec4_dot(ray->dir, d->normal);
	if (fabsf(denom) < EPSILON)
		return (false);
	t = vec4_dot(vec4_sub(d->center, ray->origin), d->normal) / denom;
	if (t < EPSILON || t > d->t_max)
		return (false);
	p = ray_at(ray, t);
	if (vec4_len_sq(vec4_sub(p, d->center)) > (d->radius * d->radius))
		return (false);
	rec->t = t;
	rec->p = p;
	hit_set_face_normal(rec, ray, d->normal);
	return (true);
}

static inline bool	init_cy_eq(const t_cylinder *cy, const t_ray *r,
		t_cy_eq *eq)
{
	eq->oc = vec4_sub(r->origin, cy->center);
	eq->dot_dv = vec4_dot(r->dir, cy->axis);
	eq->dot_ocv = vec4_dot(eq->oc, cy->axis);
	eq->a = 1.0f - (eq->dot_dv * eq->dot_dv);
	if (fabsf(eq->a) < EPSILON)
		return (false);
	eq->half_b = vec4_dot(eq->oc, r->dir) - (eq->dot_ocv * eq->dot_dv);
	eq->c = vec4_len_sq(eq->oc) - (eq->dot_ocv * eq->dot_ocv)
		- (cy->radius * cy->radius);
	eq->disc = (eq->half_b * eq->half_b) - (eq->a * eq->c);
	return (eq->disc >= 0.0f);
}

static inline bool	check_cy_root(const t_cylinder *cy, const t_ray *r,
		const t_cy_eq *eq, t_hit *rec)
{
	float	m;
	t_vec4	p_on_axis;

	if (rec->t <= EPSILON)
		return (false);
	m = eq->dot_dv * rec->t + eq->dot_ocv;
	if (m < -(cy->height * 0.5f) || m > (cy->height * 0.5f))
		return (false);
	rec->p = ray_at(r, rec->t);
	p_on_axis = vec4_add(cy->center, vec4_scale(cy->axis, m));
	hit_set_face_normal(rec, r, vec4_normalize(vec4_sub(rec->p, p_on_axis)));
	return (true);
}

#endif // INTERSECTIONS_CYLINDER_UTILS_H