/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_vectors.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:43:27 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/12/06 20:55:03 by rel-qoqu         ###   ########.fr       */
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

#endif // RT_VECTORS_H
