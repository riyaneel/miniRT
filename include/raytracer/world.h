/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 03:44:22 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 12:09:28 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "intersections_bvh.h"
# include "world_utils.h"

static inline bool	shadow_spheres(const t_scene *scn, const t_ray *r,
		const t_vec4 bounds)
{
	const t_sphere	*s = &scn->spheres;
	__m128			r_orig_x;
	__m128			r_orig_y;
	__m128			r_orig_z;
	__m128			r_dir_x;
	__m128			r_dir_y;
	__m128			r_dir_z;
	__m128			s_cx;
	__m128			s_cy;
	__m128			s_cz;
	__m128			s_rsq;
	__m128			oc_x;
	__m128			oc_y;
	__m128			oc_z;
	__m128			dot_oc_dir;
	__m128			dot_oc_oc;
	__m128			disc;
	__m128			sqrt_disc;
	__m128			root;
	__m128			mask;
	__m128			t_mask;
	int				mask_int;
	int				i;
	const __m128	t_min = _mm_set1_ps(bounds.x);
	const __m128	t_max = _mm_set1_ps(bounds.y);

	r_orig_x = _mm_set1_ps(r->origin.x);
	r_orig_y = _mm_set1_ps(r->origin.y);
	r_orig_z = _mm_set1_ps(r->origin.z);
	r_dir_x = _mm_set1_ps(r->dir.x);
	r_dir_y = _mm_set1_ps(r->dir.y);
	r_dir_z = _mm_set1_ps(r->dir.z);
	i = 0;
	while (i < s->count)
	{
		s_cx = _mm_loadu_ps(&s->x[i]);
		s_cy = _mm_loadu_ps(&s->y[i]);
		s_cz = _mm_loadu_ps(&s->z[i]);
		s_rsq = _mm_loadu_ps(&s->r_sq[i]);
		oc_x = _mm_sub_ps(r_orig_x, s_cx);
		oc_y = _mm_sub_ps(r_orig_y, s_cy);
		oc_z = _mm_sub_ps(r_orig_z, s_cz);
		dot_oc_dir = _mm_add_ps(_mm_mul_ps(oc_x, r_dir_x),
				_mm_add_ps(_mm_mul_ps(oc_y, r_dir_y), _mm_mul_ps(oc_z, r_dir_z)));
		dot_oc_oc = _mm_add_ps(_mm_mul_ps(oc_x, oc_x),
				_mm_add_ps(_mm_mul_ps(oc_y, oc_y), _mm_mul_ps(oc_z, oc_z)));
		const __m128	c_val = _mm_sub_ps(dot_oc_oc, s_rsq);
		disc = _mm_sub_ps(_mm_mul_ps(dot_oc_dir, dot_oc_dir), c_val);
		mask = _mm_cmpge_ps(disc, _mm_setzero_ps());
		if (_mm_movemask_ps(mask) != 0)
		{
			sqrt_disc = _mm_sqrt_ps(disc);
			root = _mm_sub_ps(_mm_mul_ps(dot_oc_dir, _mm_set1_ps(-1.0f)), sqrt_disc);
			t_mask = _mm_and_ps(_mm_cmpgt_ps(root, t_min), _mm_cmplt_ps(root, t_max));
			const __m128	root2 = _mm_add_ps(_mm_mul_ps(dot_oc_dir, _mm_set1_ps(-1.0f)), sqrt_disc);
			const __m128	t_mask2 = _mm_and_ps(_mm_cmpgt_ps(root2, t_min), _mm_cmplt_ps(root2, t_max));
			mask = _mm_and_ps(mask, _mm_or_ps(t_mask, t_mask2));
			mask_int = _mm_movemask_ps(mask);
			if (mask_int != 0)
			{
				for (int k = 0; k < 4; k++)
				{
					if ((mask_int >> k) & 1)
					{
						if (i + k < s->count)
							return (true);
					}
				}
			}
		}
		i += 4;
	}
	return (false);
}

static inline bool	shadow_planes(const t_scene *scn, const t_ray *r,
		const t_vec4 bounds)
{
	t_hit	tmp;
	int		i;

	i = 0;
	while (i < scn->num_planes)
	{
		if (hit_plane(&scn->planes[i], r, bounds, &tmp))
			return (true);
		i++;
	}
	return (false);
}

static inline bool	shadow_cylinders(const t_scene *scn, const t_ray *r,
		const t_vec4 bounds)
{
	t_hit	tmp;
	int		i;

	i = 0;
	while (i < scn->num_cylinders)
	{
		if (hit_cylinder(&scn->cylinders[i], r, bounds, &tmp))
			return (true);
		i++;
	}
	return (false);
}

static inline bool	hit_world(const t_scene *scn, const t_ray *r,
		t_vec4 bounds, t_hit *rec)
{
	bool	hit;

	hit = false;
	if (check_spheres(scn, r, &bounds, rec))
		hit = true;
	if (check_planes(scn, r, &bounds, rec))
		hit = true;
	if (check_cylinders(scn, r, &bounds, rec))
		hit = true;
	if (scn->num_meshes > 0)
	{
		if (check_meshes(scn, r, &bounds, rec))
			hit = true;
	}
	return (hit);
}

static inline bool	hit_world_any(const t_scene *scn, const t_ray *r,
		const float t_max)
{
	const t_vec4	bounds = {EPSILON, t_max, 0, 0};
	t_hit			dummy_rec;
	int				i;

	if (shadow_spheres(scn, r, bounds))
		return (true);
	if (shadow_planes(scn, r, bounds))
		return (true);
	if (shadow_cylinders(scn, r, bounds))
		return (true);
	if (scn->num_meshes > 0)
	{
		i = 0;
		while (i < scn->num_meshes)
		{
			if (hit_bvh(&scn->meshes[i], r, &dummy_rec, t_max))
				return (true);
			i++;
		}
	}
	return (false);
}

#endif // WORLD_H
