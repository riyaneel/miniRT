/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_vectors.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:43:27 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/12/06 22:35:52 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_VECTORS_H
# define RT_VECTORS_H

# include "vector_base_ops.h"

static inline float	vec4_dot(const t_vec4 a, const t_vec4 b)
{
	const t_v4sf	mul = a.v * b.v;
	const t_v4sf	shuf_high = __builtin_shufflevector(mul, mul, 2, 3, 2, 3);
	const t_v4sf	sum_high = mul + shuf_high;
	const t_v4sf	shuf_odd = __builtin_shufflevector(sum_high, sum_high,
			1, 1, 1, 1);
	const t_v4sf	sum_final = sum_high + shuf_odd;

	return ((t_vec4){.v = sum_final}.x);
}

static inline t_vec4	vec4_cross(const t_vec4 a, const t_vec4 b)
{
	const t_v4sf	a_yzx = __builtin_shufflevector(a.v, a.v, 1, 2, 0, 3);
	const t_v4sf	a_zxy = __builtin_shufflevector(a.v, a.v, 2, 0, 1, 3);
	const t_v4sf	b_yzx = __builtin_shufflevector(b.v, b.v, 1, 2, 0, 3);
	const t_v4sf	b_zxy = __builtin_shufflevector(b.v, b.v, 2, 0, 1, 3);
	const t_v4sf	r_vec = (a_yzx * b_zxy) - (a_zxy * b_yzx);

	return ((t_vec4){.v = r_vec});
}

#endif // RT_VECTORS_H
