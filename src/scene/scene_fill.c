/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 08:18:48 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/16 08:20:52 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/ctype/ft_ctype.h"
#include "core/string/ft_string.h"
#include "scene/scene_parser.h"
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
			scn->num_spheres++;
		else if (!ft_strncmp(p, "pl", 2) && ft_isspace(p[2]))
			scn->num_planes++;
		else if (!ft_strncmp(p, "cy", 2) && ft_isspace(p[2]))
			scn->num_cylinders++;
		while (*p && *p != '\n')
			p++;
		if (*p == '\n')
			p++;
	}
}

static void	parse_global(t_scene *scn, char **p)
{
	if (**p == 'A' && ft_isspace((*p)[1]))
	{
		(*p)++;
		scn->ambient.ratio = parse_float(p);
		scn->ambient.color = vec4_scale(parse_color(p), scn->ambient.ratio);
		scn->has_amb = true;
	}
	else if (**p == 'C' && ft_isspace((*p)[1]))
	{
		(*p)++;
		scn->camera.origin = parse_vec3(p, 1.0f);
		scn->camera.dir = vec4_normalize(parse_vec3(p, 0.0f));
		scn->camera.fov = parse_float(p);
		scn->has_cam = true;
	}
	else if (**p == 'L' && ft_isspace((*p)[1]))
	{
		(*p)++;
		scn->light.origin = parse_vec3(p, 1.0f);
		scn->light.ratio = parse_float(p);
		scn->light.color = parse_color(p);
		scn->has_light = true;
	}
}

static void	process_line(t_scene *scn, char **p, int *counts)
{
	skip_formatting(p);
	if (!**p)
		return ;
	if (**p == 'A' || **p == 'C' || **p == 'L')
		parse_global(scn, p);
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
		process_line(scn, &p, counts);
	return (true);
}
