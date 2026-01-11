/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 22:18:19 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/11 22:37:01 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/scene_parser.h"
#include "vectors/rt_vectors.h"

void	parse_cylinder(t_scene *scn, int *idx, char **p)
{
	t_cylinder	*cylinder;

	cylinder = &scn->cylinders[(*idx)++];
	(*p) += 2;
	cylinder->center = parse_vec3(p, 1.0f);
	cylinder->axis = vec4_normalize(parse_vec3(p, 0.0f));
	cylinder->radius = parse_float(p) * 0.5f;
	cylinder->height = parse_float(p);
	cylinder->color = parse_color(p);
}
