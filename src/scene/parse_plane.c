/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 22:18:11 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/11 22:35:03 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/scene_parser.h"
#include "vectors/rt_vectors.h"

void	parse_plane(const t_scene *scn, int *idx, char **p)
{
	t_plane	*plane;

	plane = &scn->planes[(*idx)++];
	(*p) += 2;
	plane->point = parse_vec3(p, 1.0f);
	plane->normal = vec4_normalize(parse_vec3(p, 0.0f));
	plane->color = parse_color(p);
}
