/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_bvh.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:56:24 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/16 11:49:01 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTIONS_BVH_H
# define INTERSECTIONS_BVH_H

# include "intersections.h"
# include "scene/mesh_types.h"
# include "utils/maths_utils.h"

static inline bool	intersect_aabb(const t_ray *r, const t_aabb *b,
		const float t_max)
{
	const t_vec4	inv = vec4_div((t_vec4){{1, 1, 1, 1}}, r->dir);
	const t_vec4	t0 = vec4_mul(vec4_sub(b->min, r->origin), inv);
	const t_vec4	t1 = vec4_mul(vec4_sub(b->max, r->origin), inv);
	const t_vec4	t_min = vec4_min(t0, t1);
	const t_vec4	t_max_v = vec4_max(t0, t1);
	const float		tin = fmax_fast(t_min.x, fmax_fast(t_min.y, t_min.z));
	const float		tout = fmin_fast(t_max_v.x, fmin_fast(t_max_v.y, t_max_v.z));

	return (tout >= tin && tin < t_max && tout > 0);
}

static inline bool	intersect_tri(const t_ray *r, const t_triangle *tr,
		t_hit *rec, const float t_max)
{
	const t_vec4	pvec = vec4_cross(r->dir, tr->e2);
	const float		det = vec4_dot(tr->e1, pvec);
	float			inv_det;
	t_vec4			tvec;
	t_vec4			qvec;
	float			u;
	float			v;
	float			t;

	if (fabsf(det) < 0.000001f)
		return (false);
	inv_det = 1.0f / det;
	tvec = vec4_sub(r->origin, tr->v0);
	u = vec4_dot(tvec, pvec) * inv_det;
	if (u < 0.0f || u > 1.0f)
		return (false);
	qvec = vec4_cross(tvec, tr->e1);
	v = vec4_dot(r->dir, qvec) * inv_det;
	if (v < 0.0f || u + v > 1.0f)
		return (false);
	t = vec4_dot(tr->e2, qvec) * inv_det;
	if (t < EPSILON || t > t_max)
		return (false);
	rec->t = t;
	rec->p = ray_at(r, t);
	rec->normal = tr->normal;
	return (true);
}

static inline bool	hit_bvh(const t_mesh *m, const t_ray *r,
		t_hit *rec, const float t_max)
{
	int			stack[64];
	int			sp;
	int			idx;
	bool		hit;
	int			i;

	sp = 0;
	stack[sp++] = 0;
	hit = false;
	rec->t = t_max;
	while (sp > 0)
	{
		idx = stack[--sp];
		if (!intersect_aabb(r, &m->bvh_nodes[idx].bounds, rec->t))
			continue ;
		if (m->bvh_nodes[idx].tri_count > 0)
		{
			i = 0;
			while (i < m->bvh_nodes[idx].tri_count)
			{
				if (intersect_tri(r, &m->tris[m->bvh_nodes[idx].first_tri_idx
							+ i], rec, rec->t))
					hit = true;
				i++;
			}
		}
		else
		{
			stack[sp++] = m->bvh_nodes[idx].left_child + 1;
			stack[sp++] = m->bvh_nodes[idx].left_child;
		}
	}
	return (hit);
}

#endif // INTERSECTIONS_BVH_H
