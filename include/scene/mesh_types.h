/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_types.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 09:31:09 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/17 14:28:03 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_TYPES_H
# define MESH_TYPES_H

# include "allocator/arena_allocator.h"
# include "vectors/rt_vectors.h"

typedef struct s_triangle {
	t_vec4	v0;
	t_vec4	e1;
	t_vec4	e2;
	t_vec4	geo_normal;
} __attribute__((aligned(16)))	t_triangle;

typedef struct s_aabb {
	t_vec4	min;
	t_vec4	max;
} __attribute__((aligned(16)))	t_aabb;

typedef struct s_bvh_node {
	t_aabb	bounds;
	union {
		int	left_child;
		int	first_tri_idx;
	};
	int		tri_count;
	long	padding[3];
} __attribute__((aligned(16)))	t_bvh_node;

typedef struct s_mesh {
	t_triangle	*tris;
	t_bvh_node	*bvh_nodes;
	t_aabb		bounds;
	t_vec4		color;
	int			num_tris;
	int			num_nodes;
	long		padding;
}	t_mesh;

#endif // MESH_TYPES_H
