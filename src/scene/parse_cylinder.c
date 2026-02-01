/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 22:18:19 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 12:55:50 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/scene_parser.h"
#include "scene/scene_validate.h"
#include "vectors/rt_vectors.h"

void	parse_cylinder(t_scene *scn, int *idx, char **p)
{
	t_cylinder	*cylinder;
	t_vec4		axis;

	cylinder = &scn->cylinders[(*idx)++];
	(*p) += 2;
	cylinder->center = parse_vec3(p, 1.0f);
	axis = parse_vec3(p, 0.0f);
	validate_normalized_vec(axis, "Cylinder axis");
	cylinder->axis = vec4_normalize(axis);
	cylinder->radius = parse_float(p) * 0.5f;
	cylinder->height = parse_float(p);
	cylinder->color = parse_color(p);
}
