/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vec3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 22:17:36 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/11 22:25:14 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/scene_parser.h"

t_vec4	parse_vec3(char **p, const float w)
{
	t_vec4	vec;

	vec.x = parse_float(p);
	skip_formatting(p);
	if (**p == ',')
		(*p)++;
	vec.y = parse_float(p);
	skip_formatting(p);
	if (**p == ',')
		(*p)++;
	vec.z = parse_float(p);
	skip_formatting(p);
	if (**p == ',')
		(*p)++;
	vec.w = w;
	return (vec);
}
