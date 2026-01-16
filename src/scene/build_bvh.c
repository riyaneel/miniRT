/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_bvh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 09:58:32 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/16 11:48:07 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>

#include "scene/scene_parser.h"

static t_aabb	get_bounds(const t_triangle *tris, const int count)
{
	t_aabb	b;
	t_vec4	p;
	int		i;

	b.min = (t_vec4){{FLT_MAX, FLT_MAX, FLT_MAX, 1}};
	b.max = (t_vec4){{-FLT_MAX, -FLT_MAX, -FLT_MAX, 1}};
	i = -1;
	while (++i < count)
	{
		p = tris[i].v0;
		b.min = vec4_min(b.min, vec4_min(p, vec4_add(p, tris[i].e1)));
		b.max = vec4_max(b.max, vec4_max(p, vec4_add(p, tris[i].e1)));
		b.min = vec4_min(b.min, vec4_add(p, tris[i].e2));
		b.max = vec4_max(b.max, vec4_add(p, tris[i].e2));
	}
	b.min = vec4_sub(b.min, (t_vec4){{0.001f, 0.001f, 0.001f, 0}});
	b.max = vec4_add(b.max, (t_vec4){{0.001f, 0.001f, 0.001f, 0}});
	return (b);
}

static int	partition(t_triangle *t, const int count, const int axis,
		const float mid)
{
	int			i;
	int			j;
	t_triangle	tmp;
	t_vec4		c;

	i = 0;
	j = count - 1;
	while (i <= j)
	{
		c = vec4_add(t[i].v0, vec4_scale(vec4_add(t[i].e1, t[i].e2), 0.333f));
		if (((float *)&c)[axis] < mid)
			i++;
		else
		{
			tmp = t[i];
			t[i] = t[j];
			t[j--] = tmp;
		}
	}
	return (i);
}

static void	split(t_mesh *m, const int idx, const int start, int *pool)
{
	t_bvh_node	*n;
	t_vec4		sz;
	int			ax;
	int			mid;

	n = &m->bvh_nodes[idx];
	n->bounds = get_bounds(&m->tris[start], n->tri_count);
	if (n->tri_count <= 4)
	{
		n->first_tri_idx = start;
		return ;
	}
	sz = vec4_sub(n->bounds.max, n->bounds.min);
	ax = (sz.y > sz.x);
	if (sz.z > ((float *)&sz)[ax])
		ax = 2;
	mid = partition(&m->tris[start], n->tri_count, ax,
			((float *)&n->bounds.min)[ax] + ((float *)&sz)[ax] * 0.5f);
	if (mid == 0 || mid == n->tri_count)
		mid = n->tri_count / 2;
	n->left_child = *pool;
	*pool += 2;
	m->bvh_nodes[n->left_child].tri_count = mid;
	split(m, n->left_child, start, pool);
	m->bvh_nodes[n->left_child + 1].tri_count = n->tri_count - mid;
	split(m, n->left_child + 1, start + mid, pool);
	n->tri_count = 0;
}

void	build_bvh(t_mesh *mesh, t_arena *arena)
{
	int	pool;

	if (!mesh || mesh->num_tris == 0)
		return ;
	mesh->bvh_nodes = arena_alloc_array(arena, (size_t)mesh->num_tris * 2,
			sizeof(t_bvh_node));
	pool = 1;
	mesh->bvh_nodes[0].tri_count = mesh->num_tris;
	split(mesh, 0, 0, &pool);
	mesh->num_nodes = pool;
	mesh->bounds = mesh->bvh_nodes[0].bounds;
}
