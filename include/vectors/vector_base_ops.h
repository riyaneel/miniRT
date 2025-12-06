/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_base_ops.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 20:50:45 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/12/06 21:55:50 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_BASE_OPS_H
# define VECTOR_BASE_OPS_H

# include "vector_types.h"

/**
 * @brief Initializes a new vector with specific components.
 * @param x The x component.
 * @param y The y component.
 * @param z The z component.
 * @param w The w component (usually 0 for a direction, 1 for a point).
 * @return The initialized vector.
 */
static inline t_vec4	vec_init(float x, float y, float z, float w)
{
	return ((t_vec4){x, y, z, w});
}

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

#endif // VECTOR_BASE_OPS_H
