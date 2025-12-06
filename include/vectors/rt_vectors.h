/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_vectors.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:43:27 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/12/06 20:29:31 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_VECTORS_H
# define RT_VECTORS_H

# include "vector_types.h"

/**
 * @brief Performs component-wise addition of two vectors.
 * @note Uses SIMD instructions for parallel processing.
 * @param a The first vector.
 * @param b The second vector.
 * @return Result where r.x = a.x + b.x, etc.
 */
static inline t_vec4	vec4_add(const t_vec4 a, const t_vec4 b)
{
	return ((t_vec4){a.v + b.v});
}

/**
 * @brief Performs component-wise substraction of two vectors.
 * @note Uses SIMD instructions for parallel processing.
 * @param a The first vector.
 * @param b The second vector.
 * @return Result where r.x = a.x - b.x, etc.
 */
static inline t_vec4	vec4_sub(const t_vec4 a, const t_vec4 b)
{
	return ((t_vec4){a.v - b.v});
}

/**
 * @brief Performs component-wise multiplication (Hadamard Product) of
 *  two vectors.
 * @note Uses SIMD instructions for parallel processing.
 * @warning This is not a dot product or cross-product.
 * @param a The first vector.
 * @param b The second vector.
 * @return Result where r.x = a.x + b.x, etc.
 */
static inline t_vec4	vec4_mul(const t_vec4 a, const t_vec4 b)
{
	return ((t_vec4){a.v * b.v});
}

/**
 * @brief Performs component-wise division of two vectors.
 * @note Uses SIMD instructions for parallel processing.
 * @warning Division by zero will result in Infinity or NaN components.
 * @param a The first vector.
 * @param b The second vector.
 * @return Result where r.x = a.x + b.x, etc.
 */
static inline t_vec4	vec4_div(const t_vec4 a, const t_vec4 b)
{
	return ((t_vec4){a.v / b.v});
}

static inline float	vec4_dot(const t_vec4 a, const t_vec4 b)
{
	t_v4sf	mul;
	t_v4sf	shuf_high;
	t_v4sf	sum_high;
	t_v4sf	shuf_odd;
	t_v4sf	sum_final;

	mul = a.v * b.v;
	shuf_high = __builtin_shufflevector(mul, mul, 2, 3, 2, 3);
	sum_high = mul + shuf_high;
	shuf_odd = __builtin_shufflevector(sum_high, sum_high, 1, 1, 1, 1);
	sum_final = sum_high + shuf_odd;
	return ((t_vec4){.v = sum_final}.x);
}

#endif // RT_VECTORS_H
