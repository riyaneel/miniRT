/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 22:17:15 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/11 22:23:40 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/scene_parser.h"

#include "core/ctype/ft_ctype.h"
#include "core/stdlib/ft_stdlib.h"

float	parse_float(char **p)
{
	float	val;
	char	*s;

	skip_formatting(p);
	s = *p;
	val = (float)ft_atof(s);
	if (*s == '-' || *s == '+')
		s++;
	while (ft_isdigit(*s))
		s++;
	if (*s == '.')
	{
		s++;
		while (ft_isdigit(*s))
			s++;
	}
	*p = s;
	return (val);
}
