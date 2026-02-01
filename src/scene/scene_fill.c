/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 08:18:48 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 12:59:42 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/ctype/ft_ctype.h"
#include "core/string/ft_string.h"
#include "io/ft_printf.h"
#include "scene/scene_parser.h"
#include "scene/scene_validate.h"
#include "vectors/rt_vectors.h"

void	count_objects(t_scene *scn, char *data)
{
	char	*p;

	p = data;
	while (*p)
	{
		skip_formatting(&p);
		if (!*p)
			break ;
		if (!ft_strncmp(p, "sp", 2) && ft_isspace(p[2]))
			scn->spheres.count++;
		else if (!ft_strncmp(p, "pl", 2) && ft_isspace(p[2]))
			scn->num_planes++;
		else if (!ft_strncmp(p, "cy", 2) && ft_isspace(p[2]))
			scn->num_cylinders++;
		else if (!ft_strncmp(p, "obj", 3) && ft_isspace(p[3]))
			scn->num_meshes++;
		while (*p && *p != '\n')
			p++;
		if (*p == '\n')
			p++;
	}
}

static bool	parse_ambient(t_scene *scn, char **p)
{
	if (scn->has_amb)
	{
		ft_dprintf(2, "Error\nAmbient light (A) already defined\n");
		return (false);
	}
	(*p)++;
	scn->ambient.ratio = parse_float(p);
	if (!validate_ratio(scn->ambient.ratio, "Ambient"))
		return (false);
	scn->ambient.color = vec4_scale(parse_color(p), scn->ambient.ratio);
	scn->has_amb = true;
	return (true);
}

static bool	parse_camera(t_scene *scn, char **p)
{
	t_vec4	dir;

	if (scn->has_cam)
	{
		ft_dprintf(2, "Error\nCamera (C) already defined\n");
		return (false);
	}
	(*p)++;
	scn->camera.origin = parse_vec3(p, 1.0f);
	dir = parse_vec3(p, 0.0f);
	if (!validate_normalized_vec(dir, "Camera direction"))
		return (false);
	scn->camera.dir = vec4_normalize(dir);
	scn->camera.fov = parse_float(p);
	if (!validate_fov(scn->camera.fov))
		return (false);
	scn->has_cam = true;
	return (true);
}

static bool	parse_light(t_scene *scn, char **p)
{
	if (scn->has_light)
	{
		ft_dprintf(2, "Error\nLight (L) already defined\n");
		return (false);
	}
	(*p)++;
	scn->light.origin = parse_vec3(p, 1.0f);
	scn->light.ratio = parse_float(p);
	if (!validate_ratio(scn->light.ratio, "Light"))
		return (false);
	scn->light.color = parse_color(p);
	scn->has_light = true;
	return (true);
}

static bool	parse_global(t_scene *scn, char **p)
{
	if (**p == 'A' && ft_isspace((*p)[1]))
		return (parse_ambient(scn, p));
	if (**p == 'C' && ft_isspace((*p)[1]))
		return (parse_camera(scn, p));
	if (**p == 'L' && ft_isspace((*p)[1]))
		return (parse_light(scn, p));
	return (true);
}

static bool	process_line(t_scene *scn, char **p, int *counts)
{
	bool	success;

	success = true;
	skip_formatting(p);
	if (!**p)
		return (success);
	if (**p == 'A' || **p == 'C' || **p == 'L')
		success = parse_global(scn, p);
	else if (!ft_strncmp(*p, "sp", 2))
		parse_sphere(scn, &counts[0], p);
	else if (!ft_strncmp(*p, "pl", 2))
		parse_plane(scn, &counts[1], p);
	else if (!ft_strncmp(*p, "cy", 2))
		parse_cylinder(scn, &counts[2], p);
	while (**p && **p != '\n')
		(*p)++;
	if (**p == '\n')
		(*p)++;
	return (success);
}

bool	fill_objects(t_scene *scn, char *data)
{
	char	*p;
	int		counts[3];

	counts[0] = 0;
	counts[1] = 0;
	counts[2] = 0;
	p = data;
	while (*p)
	{
		if (!process_line(scn, &p, counts))
			return (false);
	}
	return (true);
}
