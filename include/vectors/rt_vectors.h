/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_vectors.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:43:27 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/14 14:30:03 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_VECTORS_H
# define RT_VECTORS_H

# include <float.h>

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

static inline t_vec4	vec4_normalize(const t_vec4 vec)
{
	t_v4sf	work;
	t_v4sf	shuf;
	t_v4sf	len_sq;
	t_v4sf	inv;

	work = vec.v * vec.v;
	shuf = __builtin_shufflevector(work, work, 2, 3, 2, 3);
	work += shuf;
	shuf = __builtin_shufflevector(work, work, 1, 1, 1, 1);
	work += shuf;
	len_sq = __builtin_shufflevector(work, work, 0, 0, 0, 0);
	inv = __builtin_ia32_rsqrtps(len_sq);
	inv = inv * (1.5f - 0.5f * len_sq * inv * inv);
	return ((t_vec4){.v = vec.v * inv});
}

static inline float	vec4_len_sq(const t_vec4 vec)
{
	return (vec4_dot(vec, vec));
}

static inline float	vec4_len(const t_vec4 vec)
{
	const float	eps = FLT_EPSILON;
	float		ls;
	t_v4sf		vals;
	t_v4sf		safe_vals;
	t_v4sf		inv;

	ls = vec4_len_sq(vec);
	vals = (t_v4sf){ls, ls, ls, ls};
	safe_vals = __builtin_ia32_maxps(vals, (t_v4sf){eps, eps, eps, eps});
	inv = __builtin_ia32_rsqrtps(safe_vals);
	return (ls * (t_vec4){.v = inv}.x);
}

#endif // RT_VECTORS_H
