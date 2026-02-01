/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 13:15:44 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 18:18:17 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/scene_parser.h"

#include "core/ctype/ft_ctype.h"
#include "core/string/ft_string.h"

__attribute__((always_inline))
static inline void	count_primitive(t_scene *scn, const char *p)
{
	if (!ft_strncmp(p, "sp", 2) && ft_isspace(p[2]))
		scn->spheres.count++;
	else if (!ft_strncmp(p, "pl", 2) && ft_isspace(p[2]))
		scn->num_planes++;
	else if (!ft_strncmp(p, "cy", 2) && ft_isspace(p[2]))
		scn->num_cylinders++;
	else if (!ft_strncmp(p, "co", 2) && ft_isspace(p[2]))
		scn->num_cones++;
	else if (!ft_strncmp(p, "obj", 3) && ft_isspace(p[3]))
		scn->num_meshes++;
	else if (*p == 'L' && ft_isspace(p[1]))
		scn->num_lights++;
}

void	count_objects(t_scene *scn, char *data)
{
	char	*p;

	p = data;
	while (*p)
	{
		skip_formatting(&p);
		if (!*p)
			break ;
		count_primitive(scn, p);
		while (*p && *p != '\n')
			p++;
		if (*p == '\n')
			p++;
	}
}
