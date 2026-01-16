/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 09:05:33 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/16 11:49:53 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

#include "scene/scene_parser.h"

#include "core/ctype/ft_ctype.h"
#include "core/memory/ft_memory.h"

static bool	alloc_arrays(t_arena *arena, t_scene *scn)
{
	if (scn->num_spheres)
		scn->spheres = arena_alloc_align(arena, sizeof(t_sphere)
				* (size_t)scn->num_spheres, 16);
	if (scn->num_planes)
		scn->planes = arena_alloc_align(arena, sizeof(t_plane)
				* (size_t)scn->num_planes, 16);
	if (scn->num_cylinders)
		scn->cylinders = arena_alloc_align(arena, sizeof(t_cylinder)
				* (size_t)scn->num_cylinders, 16);
	if ((scn->num_spheres && !scn->spheres)
		|| (scn->num_planes && !scn->planes)
		|| (scn->num_cylinders && !scn->cylinders))
		return (false);
	return (true);
}

static void	load_mesh_resource(t_scene *scn, t_arena *arena, char *p)
{
	char	path[256];
	int		i;

	while (*p)
	{
		skip_formatting(&p);
		if (p[0] == 'o' && p[1] == 'b' && p[2] == 'j' && ft_isspace(p[3]))
		{
			p += 3;
			skip_formatting(&p);
			i = 0;
			while (*p && *p != '\n' && !ft_isspace(*p) && i < 255)
				path[i++] = *p++;
			path[i] = '\0';
			printf("[Mesh] Loading '%s'...\n", path);
			scn->mesh = parse_obj(arena, path);
			if (scn->mesh)
				build_bvh(scn->mesh, arena);
			return ;
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
	if (scn->mesh)
		printf("[Mesh] BVH Built: %d nodes for %d tris.\n",
			scn->mesh->num_nodes, scn->mesh->num_tris);
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
	load_mesh_resource(scn, arena, data);
	if (!validate_scene(scn))
		return (NULL);
	printf("[Scene] Parsed OK: %d Sp, %d Pl, %d Cy\n",
		scn->num_spheres, scn->num_planes, scn->num_cylinders);
	return (scn);
}
