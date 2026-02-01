/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 22:17:48 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/19 01:28:49 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/scene_parser.h"

void	parse_sphere(const t_scene *scn, int *idx, char **p)
{
	t_vec4	center;
	float	radius;
	int		i;

	i = *idx;
	(*idx)++;
	(*p) += 2;
	center = parse_vec3(p, 1.0f);
	scn->spheres.x[i] = center.x;
	scn->spheres.y[i] = center.y;
	scn->spheres.z[i] = center.z;
	radius = parse_float(p) * 0.5f;
	scn->spheres.r_sq[i] = radius * radius;
	if (radius > 0.0001f)
		scn->spheres.inv_r[i] = 1.0f / radius;
	else
		scn->spheres.inv_r[i] = 1.0f;
	scn->spheres.colors[i] = parse_color(p);
}
