/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 09:05:33 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/19 01:44:27 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

#include "scene/scene_parser.h"

#include "core/ctype/ft_ctype.h"
#include "core/memory/ft_memory.h"
#include "core/string/ft_string.h"

static inline int	align_count_simd(const int count)
{
	return ((count + 3) & ~3);
}

static bool	alloc_spheres_soa(t_arena *arena, t_scene *scn)
{
	const int	count = scn->spheres.count;
	const int	pad_count = align_count_simd(count);
	size_t		bytes_f;
	size_t		bytes_c;

	if (count == 0)
		return (true);
	bytes_f = (size_t)pad_count * sizeof(float);
	bytes_c = (size_t)pad_count * sizeof(t_vec4);
	scn->spheres.x = arena_alloc_align(arena, bytes_f, 32);
	scn->spheres.y = arena_alloc_align(arena, bytes_f, 32);
	scn->spheres.z = arena_alloc_align(arena, bytes_f, 32);
	scn->spheres.r_sq = arena_alloc_align(arena, bytes_f, 32);
	scn->spheres.inv_r = arena_alloc_align(arena, bytes_f, 32);
	scn->spheres.colors = arena_alloc_align(arena, bytes_c, 32);
	if (!scn->spheres.x || !scn->spheres.y || !scn->spheres.z
		|| !scn->spheres.r_sq || !scn->spheres.inv_r || !scn->spheres.colors)
		return (false);
	for (int i = count; i < pad_count; i++)
	{
		scn->spheres.x[i] = 0.0f;
		scn->spheres.y[i] = 0.0f;
		scn->spheres.z[i] = 0.0f;
		scn->spheres.r_sq[i] = -1.0f;
		scn->spheres.inv_r[i] = 1.0f;
		scn->spheres.colors[i] = (t_vec4){{0, 0, 0, 0}};
	}
	return (true);
}

static bool	alloc_arrays(t_arena *arena, t_scene *scn)
{
	if (!alloc_spheres_soa(arena, scn))
		return (false);
	if (scn->num_planes)
		scn->planes = arena_alloc_align(arena, sizeof(t_plane)
				* (size_t)scn->num_planes, 16);
	if (scn->num_cylinders)
		scn->cylinders = arena_alloc_align(arena, sizeof(t_cylinder)
				* (size_t)scn->num_cylinders, 16);
	if (scn->num_meshes)
		scn->meshes = arena_alloc_align(arena, sizeof(t_mesh)
				* (size_t)scn->num_meshes, 16);
	if ((scn->num_planes && !scn->planes)
		|| (scn->num_cylinders && !scn->cylinders)
		|| (scn->num_meshes && !scn->meshes))
		return (false);
	return (true);
}

static void	init_mesh_instance(t_mesh *dst, t_mesh *src, char **p)
{
	t_vec4	pos;
	float	scale;

	*dst = *src;
	pos = (t_vec4){{0, 0, 0, 1}};
	scale = 1.0f;
	skip_formatting(p);
	if (**p && (**p == '-' || ft_isdigit(**p)))
		pos = parse_vec3(p, 1.0f);
	skip_formatting(p);
	if (**p && (**p == '-' || ft_isdigit(**p)))
		scale = parse_float(p);
	skip_formatting(p);
	if (**p && (**p == '-' || ft_isdigit(**p)))
		dst->color = parse_color(p);
	else
		dst->color = (t_vec4){{0.57f, 0.77f, 0.44f, 1.0f}};
	mesh_apply_transform(dst, pos, scale);
}

static void	load_meshes(t_scene *scn, t_arena *arena, char *p)
{
	char	path[256];
	int		i;
	int		idx;
	t_mesh	*tmp;

	idx = 0;
	while (*p)
	{
		skip_formatting(&p);
		if (ft_strncmp(p, "obj", 3) == 0 && ft_isspace(p[3]))
		{
			p += 3;
			skip_formatting(&p);
			i = 0;
			while (*p && *p != '\n' && !ft_isspace(*p) && i < 255)
				path[i++] = *p++;
			path[i] = '\0';
			printf("[Mesh %d] Loading '%s'...\n", idx, path);
			tmp = parse_obj(arena, path);
			if (tmp)
			{
				init_mesh_instance(&scn->meshes[idx], tmp, &p);
				build_bvh(&scn->meshes[idx], arena);
				idx++;
			}
		}
		while (*p && *p != '\n')
			p++;
		if (*p)
			p++;
	}
}

static bool	validate_scene(const t_scene *scn)
{
	if (!scn->has_cam || !scn->has_amb || !scn->has_light)
	{
		printf("Error\nMissing mandatory scene elements (A, C, L).\n");
		return (false);
	}
	if (scn->num_meshes > 0)
		printf("[Scene] %d Meshes loaded.\n", scn->num_meshes);
	return (true);
}

t_scene	*scene_parse(t_arena *arena, const char *filename)
{
	char	*data;
	t_scene	*scn;

	data = read_file_to_arena(arena, filename);
	if (!data)
	{
		printf("Error\nCannot read file '%s'\n", filename);
		return (NULL);
	}
	scn = arena_alloc(arena, sizeof(t_scene));
	if (!scn)
		return (NULL);
	ft_bzero(scn, sizeof(t_scene));
	count_objects(scn, data);
	if (!alloc_arrays(arena, scn))
		return (NULL);
	fill_objects(scn, data);
	load_meshes(scn, arena, data);
	if (!validate_scene(scn))
		return (NULL);
	printf("[Scene] Parsed OK: %d Sp, %d Pl, %d Cy\n",
		scn->spheres.count, scn->num_planes, scn->num_cylinders);
	return (scn);
}
