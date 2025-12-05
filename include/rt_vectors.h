/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_vectors.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:43:27 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/12/05 14:24:36 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_VECTORS_H
# define RT_VECTORS_H

/**
 * @struct s_vec4
 * @brief Represents a 4-dimensional math vector.
 * * This structure is the fundamental building block for the raytracer linear
 *	algebra.<br>
 * It is used to represent:
 * - 3D points in space (where w is typically 1.0)
 * - 3D direction vectors (where w is typically 0.0)
 * - Colors (RGBA) or raw data for SIMD alignment
 * @note The 'w' component allows for matrix multiplication operations
 *  (projection, rotation, translation) using homogeneous coordinates
 * @authors Riyane
 */
typedef struct s_vec4 {
	float	x;
	float	y;
	float	z;
	float	w;
}	t_vec4;

/**
 * @typedef t_vec3
 * @brief Alias for t_vec4 used when contextually handling 3D data
 * * We use a 4D structure for 3D vectors to maintain memory alignment
 * (padding), which helps with compiler optimizations and vectorization (SIMD).
 */
typedef t_vec4	t_vec3;

#endif // RT_VECTORS_H
