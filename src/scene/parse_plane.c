/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 22:18:11 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 12:55:04 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/scene_parser.h"
#include "scene/scene_validate.h"
#include "vectors/rt_vectors.h"

void	parse_plane(const t_scene *scn, int *idx, char **p)
{
	t_plane	*plane;
	t_vec4	normal;

	plane = &scn->planes[(*idx)++];
	(*p) += 2;
	plane->point = parse_vec3(p, 1.0f);
	normal = vec4_normalize(parse_vec3(p, 0.0f));
	validate_normalized_vec(normal, "Plane normal");
	plane->normal = normal;
	plane->color = parse_color(p);
}
