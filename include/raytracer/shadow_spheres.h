/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_spheres.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 16:15:35 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 17:04:51 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADOW_SPHERES_H
# define SHADOW_SPHERES_H

# include "shadow_spheres_simd.h"

static inline bool	simd_check_mask(const int mask_int, const int i,
		const int count)
{
	int	k;

	k = 0;
	while (k < 4)
	{
		if ((mask_int >> k) & 1)
		{
			if (i + k < count)
				return (true);
		}
		k++;
	}
	return (false);
}

static inline bool	simd_test_roots(t_simd_hit *hit, const t_simd_bounds *b,
		const int i, const int count)
{
	__m128	t_mask1;
	__m128	t_mask2;
	int		mask_int;

	t_mask1 = _mm_and_ps(_mm_cmpgt_ps(hit->root1, b->t_min),
			_mm_cmplt_ps(hit->root1, b->t_max));
	t_mask2 = _mm_and_ps(_mm_cmpgt_ps(hit->root2, b->t_min),
			_mm_cmplt_ps(hit->root2, b->t_max));
	hit->mask = _mm_and_ps(hit->mask, _mm_or_ps(t_mask1, t_mask2));
	mask_int = _mm_movemask_ps(hit->mask);
	if (mask_int != 0)
		return (simd_check_mask(mask_int, i, count));
	return (false);
}

static inline bool	shadow_spheres_loop(const t_sphere *s, const t_simd_ray *sr,
		const t_simd_bounds *b)
{
	t_simd_sphere	ss;
	t_simd_oc		oc;
	t_simd_hit		hit;
	int				i;

	i = 0;
	while (i < s->count)
	{
		simd_sphere_load(&ss, s, i);
		simd_compute_oc(&oc, sr, &ss);
		simd_compute_disc(&hit, &oc, &ss);
		if (_mm_movemask_ps(hit.mask) != 0)
		{
			simd_compute_roots(&hit, &oc);
			if (simd_test_roots(&hit, b, i, s->count))
				return (true);
		}
		i += 4;
	}
	return (false);
}

static inline bool	shadow_spheres(const t_scene *scn, const t_ray *r,
		const t_vec4 bounds)
{
	t_simd_ray		sr;
	t_simd_bounds	b;

	simd_ray_init(&sr, r);
	b.t_min = _mm_set1_ps(bounds.x);
	b.t_max = _mm_set1_ps(bounds.y);
	return (shadow_spheres_loop(&scn->spheres, &sr, &b));
}

#endif // SHADOW_SPHERES_H
