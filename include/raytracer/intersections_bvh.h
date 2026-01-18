/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections_bvh.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:56:24 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/17 13:43:59 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTIONS_BVH_H
# define INTERSECTIONS_BVH_H

# include "intersections.h"
# include "scene/mesh_types.h"
# include "utils/maths_utils.h"

typedef struct s_aabb_ctx
{
	t_vec4	inv;
	t_vec4	t[2];
	t_vec4	bounds[2];
	float	limits[2];
	long	padding;
}	t_aabb_ctx;

static inline bool	intersect_aabb(const t_ray *r, const t_aabb *b,
		const float t_max)
{
	t_aabb_ctx	d;

	d.inv = vec4_div((t_vec4){{1, 1, 1, 1}}, r->dir);
	d.t[0] = vec4_mul(vec4_sub(b->min, r->origin), d.inv);
	d.t[1] = vec4_mul(vec4_sub(b->max, r->origin), d.inv);
	d.bounds[0] = vec4_min(d.t[0], d.t[1]);
	d.bounds[1] = vec4_max(d.t[0], d.t[1]);
	d.limits[0] = fmax_fast(d.bounds[0].x,
			fmax_fast(d.bounds[0].y, d.bounds[0].z));
	d.limits[1] = fmin_fast(d.bounds[1].x,
			fmin_fast(d.bounds[1].y, d.bounds[1].z));
	return (d.limits[1] >= d.limits[0]
		&& d.limits[0] < t_max && d.limits[1] > 0);
}

typedef struct s_tri_ctx
{
	t_vec4	pvec;
	t_vec4	tvec;
	t_vec4	qvec;
	float	det;
	float	inv;
	long	padding;
}	t_tri_ctx;

static inline bool	intersect_tri(const t_ray *r, const t_triangle *tr,
		t_hit *rec, const float t_max)
{
	t_tri_ctx	d;
	float		uvt[3];

	d.pvec = vec4_cross(r->dir, tr->e2);
	d.det = vec4_dot(tr->e1, d.pvec);
	if (fabsf(d.det) < 0.000001f)
		return (false);
	d.inv = 1.0f / d.det;
	d.tvec = vec4_sub(r->origin, tr->v0);
	uvt[0] = vec4_dot(d.tvec, d.pvec) * d.inv;
	if (uvt[0] < 0.0f || uvt[0] > 1.0f)
		return (false);
	d.qvec = vec4_cross(d.tvec, tr->e1);
	uvt[1] = vec4_dot(r->dir, d.qvec) * d.inv;
	if (uvt[1] < 0.0f || uvt[0] + uvt[1] > 1.0f)
		return (false);
	uvt[2] = vec4_dot(tr->e2, d.qvec) * d.inv;
	if (uvt[2] < EPSILON || uvt[2] > t_max)
		return (false);
	rec->t = uvt[2];
	rec->p = ray_at(r, uvt[2]);
	rec->normal = tr->geo_normal;
	return (true);
}

static inline void	process_leaf(const t_mesh *m, int idx,
		const t_ray *r, t_hit *rec)
{
	int		i;

	i = 0;
	while (i < m->bvh_nodes[idx].tri_count)
	{
		intersect_tri(r, &m->tris[m->bvh_nodes[idx].first_tri_idx + i],
			rec, rec->t);
		i++;
	}
}

static inline bool	hit_bvh(const t_mesh *m, const t_ray *r,
		t_hit *rec, const float t_max)
{
	int		stack[64];
	int		sp;
	int		idx;

	sp = 0;
	stack[sp++] = 0;
	rec->t = t_max;
	while (sp > 0)
	{
		idx = stack[--sp];
		if (!intersect_aabb(r, &m->bvh_nodes[idx].bounds, rec->t))
			continue ;
		if (m->bvh_nodes[idx].tri_count > 0)
			process_leaf(m, idx, r, rec);
		else
		{
			stack[sp++] = m->bvh_nodes[idx].left_child + 1;
			stack[sp++] = m->bvh_nodes[idx].left_child;
		}
	}
	return (rec->t < t_max);
}

#endif // INTERSECTIONS_BVH_H
