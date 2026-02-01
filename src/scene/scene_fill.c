/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 08:18:48 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 18:06:25 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/scene_parser.h"
#include "scene/scene_validate.h"

#include "core/string/ft_string.h"

static bool	process_line(t_scene *scn, char **p, int *counts)
{
	bool	success;

	success = true;
	skip_formatting(p);
	if (!**p)
		return (success);
	if (**p == 'A' || **p == 'C' || **p == 'L')
		success = parse_global(scn, p, &counts[4]);
	else if (!ft_strncmp(*p, "sp", 2))
		parse_sphere(scn, &counts[0], p);
	else if (!ft_strncmp(*p, "pl", 2))
		parse_plane(scn, &counts[1], p);
	else if (!ft_strncmp(*p, "cy", 2))
		parse_cylinder(scn, &counts[2], p);
	else if (!ft_strncmp(*p, "co", 2))
		parse_cone(scn, &counts[3], p);
	while (**p && **p != '\n')
		(*p)++;
	if (**p == '\n')
		(*p)++;
	return (success);
}

bool	fill_objects(t_scene *scn, char *data)
{
	char	*p;
	int		counts[5];

	counts[0] = 0;
	counts[1] = 0;
	counts[2] = 0;
	counts[3] = 0;
	counts[4] = 0;
	p = data;
	while (*p)
	{
		if (!process_line(scn, &p, counts))
			return (false);
	}
	return (true);
}
