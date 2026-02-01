/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 00:18:38 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/19 01:42:24 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTIONS_H
# define INTERSECTIONS_H

# include <math.h>

# include "ray.h"
# include "scene/scene_types.h"

# define EPSILON 0.05f

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
