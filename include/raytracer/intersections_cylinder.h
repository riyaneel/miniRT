/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_cylinder.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 16:24:33 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/14 16:39:16 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTIONS_CYLINDER_H
# define INTERSECTIONS_CYLINDER_H

# include "intersections_cylinder_utils.h"

static inline bool	solve_cylinder_caps(const t_cylinder *cy, const t_ray *ray,
		t_hit *rec, float t_closest)
{
	bool		hit_any;
	t_vec4		half_h;
	t_cap_data	cap;

	hit_any = false;
	half_h = vec4_scale(cy->axis, cy->height * 0.5f);
	cap = (t_cap_data){vec4_add(cy->center, half_h), cy->axis,
		cy->radius, t_closest, {0}};
	if (check_cap(ray, rec, &cap))
	{
		hit_any = true;
		t_closest = rec->t;
	}
	cap = (t_cap_data){vec4_sub(cy->center, half_h),
		vec4_scale(cy->axis, -1.0f), cy->radius, t_closest, {0}};
	if (check_cap(ray, rec, &cap))
		hit_any = true;
	return (hit_any);
}

static inline bool	helper(float *t_max, const float root)
{
	*t_max = root;
	return (true);
}

static inline bool	solve_cylinder_body(const t_cylinder *cy, const t_ray *r,
		t_hit *rec, float *t_max)
{
	t_cy_eq	eq;
	float	sqrtd;
	float	root;

	if (!init_cy_eq(cy, r, &eq))
		return (false);
	sqrtd = sqrtf(eq.disc);
	root = (-eq.half_b - sqrtd) / eq.a;
	if (root < *t_max)
	{
		rec->t = root;
		if (check_cy_root(cy, r, &eq, rec))
			return (helper(t_max, root));
	}
	root = (-eq.half_b + sqrtd) / eq.a;
	if (root >= *t_max)
		return (false);
	rec->t = root;
	if (check_cy_root(cy, r, &eq, rec))
		return (helper(t_max, root));
	return (false);
}

static inline bool	hit_cylinder(const t_cylinder *cy, const t_ray *r,
		t_vec4 bounds, t_hit *rec)
{
	bool	hit;
	float	closest;

	hit = false;
	closest = bounds.y;
	if (solve_cylinder_body(cy, r, rec, &closest))
		hit = true;
	if (solve_cylinder_caps(cy, r, rec, closest))
		hit = true;
	if (hit && rec->t > bounds.x && rec->t < bounds.y)
		return (true);
	return (false);
}

#endif // INTERSECTIONS_CYLINDER_H
