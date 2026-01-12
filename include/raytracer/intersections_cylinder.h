/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_cylinder.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 03:25:19 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/12 20:19:44 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTIONS_CYLINDER_H
# define INTERSECTIONS_CYLINDER_H

# include <math.h>

# include "ray.h"
# include "scene/scene_types.h"

static inline bool	check_cap(const t_vec4 center, const t_vec4 normal,
		const float radius, const t_ray *ray, t_hit *rec, const float t_max)
{
	float	denom;
	float	t;
	t_vec4	diff;
	float	len_sq;
	t_vec4	p;

	denom = vec4_dot(ray->dir, normal);
	if (fabsf(denom) < EPSILON)
		return (false);
	t = vec4_dot(vec4_sub(center, ray->origin), normal) / denom;
	if (t < EPSILON || t > t_max)
		return (false);
	p = ray_at(ray, t);
	diff = vec4_sub(p, center);
	len_sq = vec4_len_sq(diff);
	if (len_sq > (radius * radius))
		return (false);
	rec->t = t;
	rec->p = p;
	hit_set_face_normal(rec, ray, normal);
	return (true);
}

static inline bool	solve_cylinder_caps(const t_cylinder *cy, const t_ray *ray,
		t_hit *rec, float t_closest)
{
	bool	hit_any;
	t_vec4	half_h_axis;
	t_vec4	cap_top_center;
	t_vec4	cap_bot_center;

	hit_any = false;
	half_h_axis = vec4_scale(cy->axis, cy->height * 0.5f);
	cap_top_center = vec4_add(cy->center, half_h_axis);
	if (check_cap(cap_top_center, cy->axis, cy->radius, ray, rec, t_closest))
	{
		hit_any = true;
		t_closest = rec->t;
	}
	cap_bot_center = vec4_sub(cy->center, half_h_axis);
	if (check_cap(cap_bot_center, vec4_scale(cy->axis, -1.0f),
			cy->radius, ray, rec, t_closest))
		hit_any = true;
	return (hit_any);
}

static inline bool	solve_cylinder_body(const t_cylinder *cy, const t_ray *r,
		t_hit *rec, float *t_limit_ptr)
{
	t_vec4	oc;
	float	a;
	float	half_b;
	float	c;
	float	discriminant;
	float	sqrtd;
	float	root;
	float	m;
	float	dot_dv;
	float	dot_ocv;
	t_vec4	axis_comp;
	t_vec4	p_on_axis;
	t_vec4	outward_normal;

	oc = vec4_sub(r->origin, cy->center);
	dot_dv = vec4_dot(r->dir, cy->axis);
	dot_ocv = vec4_dot(oc, cy->axis);
	a = 1.0f - (dot_dv * dot_dv);
	if (fabsf(a) < EPSILON)
		return (false);
	half_b = vec4_dot(oc, r->dir) - (dot_ocv * dot_dv);
	c = vec4_len_sq(oc) - (dot_ocv * dot_ocv) - (cy->radius * cy->radius);
	discriminant = (half_b * half_b) - (a * c);
	if (discriminant < 0.0f)
		return (false);
	sqrtd = sqrtf(discriminant);
	root = (-half_b - sqrtd) / a;
	if (root > EPSILON && root < *t_limit_ptr)
	{
		m = dot_dv * root + dot_ocv;
		if (m >= -(cy->height * 0.5f) && m <= (cy->height * 0.5f))
		{
			rec->t = root;
			rec->p = ray_at(r, rec->t);
			axis_comp = vec4_scale(cy->axis, m);
			p_on_axis = vec4_add(cy->center, axis_comp);
			outward_normal = vec4_normalize(vec4_sub(rec->p, p_on_axis));
			hit_set_face_normal(rec, r, outward_normal);
			*t_limit_ptr = root;
			return (true);
		}
	}
	root = (-half_b + sqrtd) / a;
	if (root > EPSILON && root < *t_limit_ptr)
	{
		m = dot_dv * root + dot_ocv;
		if (m >= -(cy->height * 0.5f) && m <= (cy->height * 0.5f))
		{
			rec->t = root;
			rec->p = ray_at(r, rec->t);
			axis_comp = vec4_scale(cy->axis, m);
			p_on_axis = vec4_add(cy->center, axis_comp);
			outward_normal = vec4_normalize(vec4_sub(rec->p, p_on_axis));
			hit_set_face_normal(rec, r, outward_normal);
			*t_limit_ptr = root;
			return (true);
		}
	}
	return (false);
}

static inline bool	hit_cylinder(const t_cylinder *cy, const t_ray *r,
		float t_min, float t_max, t_hit *rec)
{
	bool	hit;
	float	closest_so_far;

	hit = false;
	closest_so_far = t_max;
	if (solve_cylinder_body(cy, r, rec, &closest_so_far))
		hit = true;
	if (solve_cylinder_caps(cy, r, rec, closest_so_far))
		hit = true;
	if (hit && rec->t > t_min && rec->t < t_max)
		return (true);
	return (false);
}

#endif // INTERSECTIONS_CYLINDER_H
