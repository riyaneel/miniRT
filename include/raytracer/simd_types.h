/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simd_types.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 16:12:58 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 17:04:23 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMD_TYPES_H
# define SIMD_TYPES_H

# include <immintrin.h>

typedef struct s_simd_ray
{
	__m128	orig_x;
	__m128	orig_y;
	__m128	orig_z;
	__m128	dir_x;
	__m128	dir_y;
	__m128	dir_z;
}	t_simd_ray;

typedef struct s_simd_sphere
{
	__m128	cx;
	__m128	cy;
	__m128	cz;
	__m128	r_sq;
}	t_simd_sphere;

typedef struct s_simd_oc
{
	__m128	x;
	__m128	y;
	__m128	z;
	__m128	dot_dir;
	__m128	dot_oc;
}	t_simd_oc;

typedef struct s_simd_hit
{
	__m128	disc;
	__m128	sqrt_disc;
	__m128	root1;
	__m128	root2;
	__m128	mask;
}	t_simd_hit;

typedef struct s_simd_bounds
{
	__m128	t_min;
	__m128	t_max;
}	t_simd_bounds;

#endif // SIMD_TYPES_H
