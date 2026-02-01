/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_spheres_simd.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 16:14:09 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 17:04:42 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADOW_SPHERES_SIMD_H
# define SHADOW_SPHERES_SIMD_H

# include "ray.h"
# include "simd_types.h"
# include "scene/scene_types.h"

static inline void	simd_ray_init(t_simd_ray *sr, const t_ray *r)
{
	sr->orig_x = _mm_set1_ps(r->origin.x);
	sr->orig_y = _mm_set1_ps(r->origin.y);
	sr->orig_z = _mm_set1_ps(r->origin.z);
	sr->dir_x = _mm_set1_ps(r->dir.x);
	sr->dir_y = _mm_set1_ps(r->dir.y);
	sr->dir_z = _mm_set1_ps(r->dir.z);
}

static inline void	simd_sphere_load(t_simd_sphere *ss, const t_sphere *s,
		const int i)
{
	ss->cx = _mm_loadu_ps(&s->x[i]);
	ss->cy = _mm_loadu_ps(&s->y[i]);
	ss->cz = _mm_loadu_ps(&s->z[i]);
	ss->r_sq = _mm_loadu_ps(&s->r_sq[i]);
}

static inline void	simd_compute_oc(t_simd_oc *oc, const t_simd_ray *sr,
		const t_simd_sphere *ss)
{
	oc->x = _mm_sub_ps(sr->orig_x, ss->cx);
	oc->y = _mm_sub_ps(sr->orig_y, ss->cy);
	oc->z = _mm_sub_ps(sr->orig_z, ss->cz);
	oc->dot_dir = _mm_add_ps(_mm_mul_ps(oc->x, sr->dir_x),
			_mm_add_ps(_mm_mul_ps(oc->y, sr->dir_y),
				_mm_mul_ps(oc->z, sr->dir_z)));
	oc->dot_oc = _mm_add_ps(_mm_mul_ps(oc->x, oc->x),
			_mm_add_ps(_mm_mul_ps(oc->y, oc->y),
				_mm_mul_ps(oc->z, oc->z)));
}

static inline void	simd_compute_disc(t_simd_hit *hit, const t_simd_oc *oc,
		const t_simd_sphere *ss)
{
	__m128	c_val;

	c_val = _mm_sub_ps(oc->dot_oc, ss->r_sq);
	hit->disc = _mm_sub_ps(_mm_mul_ps(oc->dot_dir, oc->dot_dir), c_val);
	hit->mask = _mm_cmpge_ps(hit->disc, _mm_setzero_ps());
}

static inline void	simd_compute_roots(t_simd_hit *hit, const t_simd_oc *oc)
{
	__m128	neg_b;

	hit->sqrt_disc = _mm_sqrt_ps(hit->disc);
	neg_b = _mm_mul_ps(oc->dot_dir, _mm_set1_ps(-1.0f));
	hit->root1 = _mm_sub_ps(neg_b, hit->sqrt_disc);
	hit->root2 = _mm_add_ps(neg_b, hit->sqrt_disc);
}

#endif // SHADOW_SPHERES_SIMD_H
