/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_cone.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 18:08:46 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 18:18:58 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTIONS_CONE_H
# define INTERSECTIONS_CONE_H

# include "intersections_cone_utils.h"

static inline bool	solve_cone_body(const t_cone *co, const t_ray *r,
		t_hit *rec, float *t_max)
{
	t_cone_eq	eq;
	float		sqrtd;
	float		root;

	if (!init_cone_eq(co, r, &eq))
		return (false);
	sqrtd = sqrtf(eq.disc);
	root = (-eq.half_b - sqrtd) / eq.a;
	if (root > EPSILON && root < *t_max)
	{
		rec->t = root;
		if (check_cone_root(co, r, &eq, rec))
		{
			*t_max = root;
			return (true);
		}
	}
	root = (-eq.half_b + sqrtd) / eq.a;
	if (root <= EPSILON || root >= *t_max)
		return (false);
	rec->t = root;
	if (check_cone_root(co, r, &eq, rec))
	{
		*t_max = root;
		return (true);
	}
	return (false);
}

static inline bool	hit_cone(const t_cone *co, const t_ray *r,
		const t_vec4 bounds, t_hit *rec)
{
	bool	hit;
	float	closest;

	hit = false;
	closest = bounds.y;
	if (solve_cone_body(co, r, rec, &closest))
		hit = true;
	if (check_cone_cap(r, co, rec, closest))
		hit = true;
	if (hit && rec->t > bounds.x && rec->t < bounds.y)
		return (true);
	return (false);
}

#endif // INTERSECTIONS_CONE_H
