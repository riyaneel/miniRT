/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_cone.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 18:08:46 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 19:41:46 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTIONS_CONE_H
# define INTERSECTIONS_CONE_H

# include "intersections_cone_utils.h"

static inline bool	try_root(const t_cone *co, const t_ray *r,
		const t_cone_eq *eq, t_hit *rec)
{
	if (rec->t <= EPSILON)
		return (false);
	return (check_cone_root(co, r, eq, rec));
}

static inline bool	test_root(const t_cone *co, const t_ray *r,
		const t_cone_eq *eq, t_hit *rec)
{
	float	root;

	root = (-eq->half_b - eq->disc) / eq->a;
	if (root > EPSILON && root < rec->t)
	{
		rec->t = root;
		if (try_root(co, r, eq, rec))
			return (true);
	}
	root = (-eq->half_b + eq->disc) / eq->a;
	if (root > EPSILON && root < rec->t)
	{
		rec->t = root;
		if (try_root(co, r, eq, rec))
			return (true);
	}
	return (false);
}

static inline bool	solve_cone_body(const t_cone *co, const t_ray *r,
		t_hit *rec, const float t_max)
{
	t_cone_eq	eq;

	if (!init_cone_eq(co, r, &eq))
		return (false);
	eq.disc = sqrtf(eq.disc);
	rec->t = t_max;
	return (test_root(co, r, &eq, rec));
}

static inline bool	hit_cone(const t_cone *co, const t_ray *r,
		const t_vec4 bounds, t_hit *rec)
{
	bool	hit;
	float	closest;

	hit = false;
	closest = bounds.y;
	if (solve_cone_body(co, r, rec, closest))
	{
		hit = true;
		closest = rec->t;
	}
	if (check_cone_cap(r, co, rec, closest))
		hit = true;
	return (hit && rec->t > bounds.x && rec->t < bounds.y);
}

#endif // INTERSECTIONS_CONE_H
