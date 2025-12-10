/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:11:44 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/12/10 20:15:26 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHS_UTILS_H
# define MATHS_UTILS_H

/**
 * @brief Branchless minimum between two floats.<br>
 * * This wrapper ensures the compiler uses the 'minss'
 * (Min Scalar Single-Precision) assembly instruction instead of comparisons
 * and jumps.
 * @note Crucial for performance in hot loops (like ray intersection).
 * @param a The first value.
 * @param b The second value.
 * @return The smaller value between a and b.
 */
static inline float	fmin_fast(const float a, const float b)
{
	return (__builtin_fminf(a, b));
}

/**
* @brief Branchless maximum between two floats.<br>
 * * This wrapper ensures the compiler uses the `maxss`
 * (Max Scalar Single-Precision) assembly instruction.
 * @note Avoiding branching prevents pipeline stalls on the CPU.
 * @param a The first value.
 * @param b The second value.
 * @return The larger value between a and b.
 */
static inline float	fmax_fast(const float a, const float b)
{
	return (__builtin_fmaxf(a, b));
}

/**
 * @brief Clamps a value within a specified range [min, max].
 * - If x is less than min, returns min.
 * - If x is greater than max, returns max.
 * - Otherwise, returns x.
 * @note Implemented using fast min/max to remain branchless.
 * @param x The value to clamp.
 * @param min The lower bound.
 * @param max The upper bound.
 * @return The clamped value.
 */
static inline float	fclamp(const float x, const float min, const float max)
{
	return (fmin_fast(fmax_fast(x, min), max));
}

/**
 * @brief Linear Interpolation (LERP).
 * * Interpolates between `x` and `y` based on the alpha value `a`.
 * * Formula: `x + a * (y - x)`
 * @param x The start value (returned when a = 0).
 * @param y The end value (returned when a = 1).
 * @param a The interpolation factor, typically in range [0.0, 1.0].
 * @return The interpolated float value.
 * @note This implementation is FMA (Fused Multiply-Add) friendly, meaning
 * modern CPUs can execute the multiplication and addition in a single cycle
 * with higher precision.
 */
static inline float	flerp(const float x, const float y, const float a)
{
	return (x + a * (y - x));
}

#endif // MATHS_UTILS_H
