/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_vectors.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:43:27 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/12/06 08:07:54 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_VECTORS_H
# define RT_VECTORS_H

/**
 * @typedef t_v4sf
 * @brief Internal type for vector extension (SIMD).
 * <br>Contains 4 floats (16 bytes) processed simultaneously by the CPU.
 */
typedef float	t_v4sf __attribute__((vector_size(16)));

/**
 * @union u_vec4
 * @brief Represents a 4-dimensional mathematical vector.
 * <br>This structure is the fundamental building block for the raytracer
 * linear algebra.
 * <br>It allows data access either as a SIMD vector (v) or via individual
 * components (x, y, z, w).
 * <br>Typical uses:
 * - 3D points in space (where w is typically 1.0)
 * - 3D direction vectors (where w is typically 0.0)
 * - Colors (RGBA)
 * @note The 'w' component allows for matrix multiplication operations
 * (projection, rotation, translation) using homogeneous coordinates.
 * @note The `aligned(16)` attribute is crucial to prevent segmentation faults
 * when using SSE/AVX instructions.
 * @author Riyane
 */
typedef union u_vec4 {
	t_v4sf	v;
	struct {
		float	x;
		float	y;
		float	z;
		float	w;
	};
} __attribute__((aligned(16)))	t_vec4;

/**
 * @typedef t_vec3
 * @brief Alias for t_vec4 used when contextually handling 3D data.
 * <br>Although we logically manipulate x, y, and z, we use a 4D structure to
 * maintain memory alignment (padding).
 * <br>This facilitates compiler optimizations and vectorization (SIMD), with
 * the 'w' component being ignored or used for alignment.
 */
typedef t_vec4	t_vec3;

static inline t_vec4	vec_init(float x, float y, float z, float w)
{
	return ((t_vec4){x, y, z, w});
}

static inline t_vec4	vec4_add(const t_vec4 a, const t_vec4 b)
{
	return ((t_vec4){a.v + b.v});
}

static inline t_vec4	vec4_sub(const t_vec4 a, const t_vec4 b)
{
	return ((t_vec4){a.v - b.v});
}

static inline t_vec4	vec4_mul(const t_vec4 a, const t_vec4 b)
{
	return ((t_vec4){a.v * b.v});
}

static inline t_vec4	vec4_div(const t_vec4 a, const t_vec4 b)
{
	return ((t_vec4){a.v / b.v});
}

#endif // RT_VECTORS_H
