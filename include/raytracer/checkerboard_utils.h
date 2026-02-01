/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard_utils.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 17:21:54 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 17:35:33 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKERBOARD_UTILS_H
# define CHECKERBOARD_UTILS_H

# include <math.h>

# include "vectors/vector_types.h"

static inline int	checker_pattern(const float u, const float v,
		const float scale)
{
	int	iu;
	int	iv;

	iu = (int)floorf(u * scale);
	iv = (int)floorf(v * scale);
	return ((iu ^ iv) & 1);
}

static inline t_vec4	checker_blend(const t_vec4 c1, const int check)
{
	t_vec4	c2;
	t_vec4	result;
	float	f;

	c2 = vec_init(0.1f, 0.1f, 0.1f, 1.0f);
	f = (float)check;
	result.x = c1.x * (1.0f - f) + c2.x * f;
	result.y = c1.y * (1.0f - f) + c2.y * f;
	result.z = c1.z * (1.0f - f) + c2.z * f;
	result.w = 1.0f;
	return (result);
}

#endif // CHECKERBOARD_UTILS_H
