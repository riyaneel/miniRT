/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 09:05:33 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 13:31:14 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/scene_parser.h"

#include "core/memory/ft_memory.h"
#include "io/ft_printf.h"

static bool	validate_scene(const t_scene *scn)
{
	if (!scn->has_cam || !scn->has_amb || !scn->has_light)
	{
		ft_dprintf(2, "Error\nMissing mandatory scene elements (A, C, L).\n");
		return (false);
	}
	if (scn->num_meshes > 0)
		ft_printf("[Scene] %d Meshes loaded.\n", scn->num_meshes);
	return (true);
}

static t_scene	*init_scene(t_arena *arena, char *data)
{
	t_scene	*scene;

	scene = arena_alloc(arena, sizeof(t_scene));
	if (!scene)
		return (NULL);
	ft_bzero(scene, sizeof(t_scene));
	count_objects(scene, data);
	if (!alloc_arrays(arena, scene))
		return (NULL);
	return (scene);
}

t_scene	*scene_parse(t_arena *arena, const char *filename)
{
	char	*data;
	t_scene	*scn;

	data = read_file_to_arena(arena, filename);
	if (!data)
	{
		ft_dprintf(2, "Error\nCannot read file '%s'\n", filename);
		return (NULL);
	}
	scn = init_scene(arena, data);
	if (!fill_objects(scn, data))
		return (NULL);
	load_meshes(scn, arena, data);
	if (!validate_scene(scn))
		return (NULL);
	ft_printf("[Scene] Parsed OK: %d Sp, %d Pl, %d Cy\n",
		scn->spheres.count, scn->num_planes, scn->num_cylinders);
	return (scn);
}
