/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 22:17:48 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/12 00:18:15 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/scene_parser.h"

void	parse_sphere(const t_scene *scn, int *idx, char **p)
{
	t_sphere	*sphere;

	sphere = &scn->spheres[(*idx)++];
	(*p) += 2;
	sphere->center = parse_vec3(p, 1.0f);
	sphere->radius = parse_float(p) * 0.5f;
	sphere->radius_sq = sphere->radius * sphere->radius;
	sphere->color = parse_color(p);
}
