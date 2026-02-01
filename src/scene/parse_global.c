/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_global.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 13:18:00 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 17:44:12 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "scene/scene_parser.h"
#include "scene/scene_validate.h"

#include "core/ctype/ft_ctype.h"
#include "io/ft_printf.h"

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

static bool	parse_light(const t_scene *scn, char **p, int *idx)
{
	t_light	*light;

	(*p)++;
	light = &scn->lights[*idx];
	light->origin = parse_vec3(p, 1.0f);
	light->ratio = parse_float(p);
	if (!validate_ratio(light->ratio, "Light"))
		return (false);
	light->color = parse_color(p);
	(*idx)++;
	return (true);
}

bool	parse_global(t_scene *scn, char **p, int *light_idx)
{
	if (**p == 'A' && ft_isspace((*p)[1]))
		return (parse_ambient(scn, p));
	if (**p == 'C' && ft_isspace((*p)[1]))
		return (parse_camera(scn, p));
	if (**p == 'L' && ft_isspace((*p)[1]))
		return (parse_light(scn, p, light_idx));
	return (true);
}
