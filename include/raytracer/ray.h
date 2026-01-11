/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:31:01 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/11 21:38:23 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "ray_types.h"
# include "vectors/rt_vectors.h"

static inline t_ray	ray_create(const t_vec4 origin, const t_vec4 dir)
{
	t_ray	r;

	r.origin = origin;
	r.dir = dir;
	return (r);
}

static inline t_vec4	ray_at(const t_ray *r, const float t)
{
	return (vec4_add(r->origin, vec4_scale(r->dir, t)));
}

static inline void	hit_set_face_normal(t_hit *rec, const t_ray *r,
		const t_vec4 outward_normal)
{
	rec->front_face = vec4_dot(r->dir, outward_normal) < 0.0f;
	if (rec->front_face)
		rec->normal = outward_normal;
	else
		rec->normal = vec4_scale(outward_normal, -1.0f);
}

#endif // RAY_H
