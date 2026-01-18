/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 00:18:38 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/18 02:47:00 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTIONS_H
# define INTERSECTIONS_H

# include <math.h>

# include "ray.h"
# include "scene/scene_types.h"

# define EPSILON 0.00001f

static inline bool	hit_sphere(const t_sphere *sp, const t_ray *ray,
		const t_vec4 bounds, t_hit *rec)
{
	t_vec4	oc;
	float	half_b;
	float	discriminant;
	float	sqrtd;
	float	root;

	oc = vec4_sub(ray->origin, sp->center);
	half_b = vec4_dot(oc, ray->dir);
	discriminant = (half_b * half_b) - (vec4_len_sq(oc) - sp->radius_sq);
	if (discriminant < 0.0f)
		return (false);
	sqrtd = sqrtf(discriminant);
	root = -half_b - sqrtd;
	if (root <= bounds.x || root >= bounds.y)
	{
		root = -half_b + sqrtd;
		if (root <= bounds.x || root >= bounds.y)
			return (false);
	}
	rec->t = root;
	rec->p = ray_at(ray, rec->t);
	hit_set_face_normal(rec, ray, vec4_scale(vec4_sub(rec->p, sp->center),
			1.0f / sp->radius));
	return (true);
}

static inline bool	hit_plane(const t_plane *pl, const t_ray *ray,
		const t_vec4 bounds, t_hit *rec)
{
	float	denom;
	float	t;
	t_vec4	po;

	denom = vec4_dot(ray->dir, pl->normal);
	if (fabsf(denom) < EPSILON)
		return (false);
	po = vec4_sub(pl->point, ray->origin);
	t = vec4_dot(po, pl->normal) / denom;
	if (t < bounds.x || t > bounds.y)
		return (false);
	rec->t = t;
	rec->p = ray_at(ray, t);
	hit_set_face_normal(rec, ray, pl->normal);
	return (true);
}

#endif // INTERSECTIONS_H
