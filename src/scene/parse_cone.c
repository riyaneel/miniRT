/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 18:06:25 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 18:07:54 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "scene/scene_parser.h"
#include "scene/scene_validate.h"

void	parse_cone(const t_scene *scn, int *idx, char **p)
{
	t_cone	*cone;
	t_vec4	axis;
	float	angle;

	cone = &scn->cones[(*idx)++];
	(*p) += 2;
	cone->apex = parse_vec3(p, 1.0f);
	axis = parse_vec3(p, 0.0f);
	validate_normalized_vec(axis, "Cone axis");
	cone->axis = vec4_normalize(axis);
	angle = parse_float(p) * ((float)M_PI / 180.0f);
	cone->tan2 = tanf(angle) * tanf(angle);
	cone->height = parse_float(p);
	cone->radius = cone->height * tanf(angle);
	cone->color = parse_color(p);
}
