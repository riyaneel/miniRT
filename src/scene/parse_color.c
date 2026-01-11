/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 22:17:40 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/11 22:29:52 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/scene_parser.h"
#include "utils/maths_utils.h"
#include "vectors/rt_vectors.h"

t_vec4	parse_color(char **p)
{
	t_vec4	c;

	c = parse_vec3(p, 0.0f);
	c = vec4_scale(c, 1.0f / 255.0f);
	c.x = fclamp(c.x, 0.0f, 1.0f);
	c.y = fclamp(c.y, 0.0f, 1.0f);
	c.z = fclamp(c.z, 0.0f, 1.0f);
	return (c);
}
