/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_alloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 13:21:51 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 18:18:13 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/scene_parser.h"

__attribute__((always_inline))
static inline int	align_count_simd(const int count)
{
	return ((count + 3) & ~3);
}

static inline void	init_sphere_padding(const t_scene *scn, const int start,
		const int end)
{
	int	i;

	i = start;
	while (i < end)
	{
		scn->spheres.x[i] = 0.0f;
		scn->spheres.y[i] = 0.0f;
		scn->spheres.z[i] = 0.0f;
		scn->spheres.r_sq[i] = -1.0f;
		scn->spheres.inv_r[i] = 1.0f;
		scn->spheres.colors[i] = vec_init(0, 0, 0, 0);
		i++;
	}
}

static bool	alloc_sphere_arrays(t_arena *arena, t_scene *scn, const int pad)
{
	size_t	bytes_f;
	size_t	bytes_c;

	bytes_f = (size_t)pad * sizeof(float);
	bytes_c = (size_t)pad * sizeof(t_vec4);
	scn->spheres.x = arena_alloc_align(arena, bytes_f, 32);
	scn->spheres.y = arena_alloc_align(arena, bytes_f, 32);
	scn->spheres.z = arena_alloc_align(arena, bytes_f, 32);
	scn->spheres.r_sq = arena_alloc_align(arena, bytes_f, 32);
	scn->spheres.inv_r = arena_alloc_align(arena, bytes_f, 32);
	scn->spheres.colors = arena_alloc_align(arena, bytes_c, 32);
	if (!scn->spheres.x || !scn->spheres.y || !scn->spheres.z)
		return (false);
	if (!scn->spheres.r_sq || !scn->spheres.inv_r || !scn->spheres.colors)
		return (false);
	return (true);
}

static bool	alloc_spheres_soa(t_arena *arena, t_scene *scn)
{
	int	count;
	int	pad_count;

	count = scn->spheres.count;
	pad_count = align_count_simd(count);
	if (count == 0)
		return (true);
	if (!alloc_sphere_arrays(arena, scn, pad_count))
		return (false);
	init_sphere_padding(scn, count, pad_count);
	return (true);
}

bool	alloc_arrays(t_arena *arena, t_scene *scn)
{
	if (!alloc_spheres_soa(arena, scn))
		return (false);
	if (scn->num_planes)
		scn->planes = arena_alloc_align(arena, sizeof(t_plane)
				* (size_t)scn->num_planes, 16);
	if (scn->num_cylinders)
		scn->cylinders = arena_alloc_align(arena, sizeof(t_cylinder)
				* (size_t)scn->num_cylinders, 16);
	if (scn->num_cones)
		scn->cones = arena_alloc_align(arena, sizeof(t_cone)
				* (size_t)scn->num_cones, 16);
	if (scn->num_meshes)
		scn->meshes = arena_alloc_align(arena, sizeof(t_mesh)
				* (size_t)scn->num_meshes, 16);
	if (scn->num_lights)
		scn->lights = arena_alloc_align(arena, sizeof(t_light)
				* (size_t)scn->num_lights, 16);
	if ((scn->num_planes && !scn->planes)
		|| (scn->num_cylinders && !scn->cylinders)
		|| (scn->num_cones && !scn->cones)
		|| (scn->num_meshes && !scn->meshes)
		|| (scn->num_lights && !scn->lights))
		return (false);
	return (true);
}
