/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:59:16 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 12:12:55 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_UTILS_H
# define WORLD_UTILS_H

# include <immintrin.h>

# include "raytracer/intersections.h"
# include "raytracer/intersections_cylinder.h"
# include "scene/scene_types.h"

static inline bool	check_spheres(const t_scene *scn, const t_ray *r,
		t_vec4 *bounds, t_hit *rec)
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
	bool			hit_any;
	float			t_cand[4];
	__m128			c_val;
	int				idx;
	float			t;
	t_vec4			center;
	t_vec4			normal;

	hit_any = false;
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
		c_val = _mm_sub_ps(dot_oc_oc, s_rsq);
		disc = _mm_sub_ps(_mm_mul_ps(dot_oc_dir, dot_oc_dir), c_val);
		mask = _mm_cmpge_ps(disc, _mm_setzero_ps());
		mask_int = _mm_movemask_ps(mask);
		if (mask_int != 0)
		{
			sqrt_disc = _mm_sqrt_ps(disc);
			root = _mm_sub_ps(_mm_mul_ps(dot_oc_dir, _mm_set1_ps(-1.0f)), sqrt_disc);
			t_mask = _mm_and_ps(
					_mm_cmpgt_ps(root, _mm_set1_ps(bounds->x)),
					_mm_cmplt_ps(root, _mm_set1_ps(bounds->y)));
			mask = _mm_and_ps(mask, t_mask);
			mask_int = _mm_movemask_ps(mask);
			if (mask_int != 0)
			{
				_mm_storeu_ps(t_cand, root);
				for (int k = 0; k < 4; k++)
				{
					if ((mask_int >> k) & 1)
					{
						idx = i + k;
						if (idx >= s->count)
							break ;
						t = t_cand[k];
						if (t < bounds->y)
						{
							bounds->y = t;
							hit_any = true;
							rec->t = t;
							rec->p = ray_at(r, t);
							center = (t_vec4){{s->x[idx], s->y[idx], s->z[idx], 1.0f}};
							normal = vec4_sub(rec->p, center);
							normal = vec4_scale(normal, s->inv_r[idx]);
							hit_set_face_normal(rec, r, normal);
							rec->color_obj = s->colors[idx];
						}
					}
				}
			}
		}
		i += 4;
	}
	return (hit_any);
}

static inline bool	check_planes(const t_scene *scn, const t_ray *r,
		t_vec4 *bounds, t_hit *rec)
{
	t_hit	tmp;
	bool	hit;
	int		i;

	hit = false;
	i = 0;
	while (i < scn->num_planes)
	{
		if (hit_plane(&scn->planes[i], r, *bounds, &tmp))
		{
			hit = true;
			bounds->y = tmp.t;
			*rec = tmp;
			rec->color_obj = scn->planes[i].color;
		}
		i++;
	}
	return (hit);
}

static inline bool	check_cylinders(const t_scene *scn, const t_ray *r,
		t_vec4 *bounds, t_hit *rec)
{
	t_hit	tmp;
	bool	hit;
	int		i;

	hit = false;
	i = 0;
	while (i < scn->num_cylinders)
	{
		if (hit_cylinder(&scn->cylinders[i], r, *bounds, &tmp))
		{
			hit = true;
			bounds->y = tmp.t;
			*rec = tmp;
			rec->color_obj = scn->cylinders[i].color;
		}
		i++;
	}
	return (hit);
}

static inline bool	check_meshes(const t_scene *scn, const t_ray *r,
		t_vec4 *bounds, t_hit *rec)
{
	bool	hit;
	int		i;

	hit = false;
	i = 0;
	while (i < scn->num_meshes)
	{
		if (hit_bvh(&scn->meshes[i], r, rec, bounds->y))
		{
			hit = true;
			bounds->y = rec->t;
			rec->color_obj = scn->meshes[i].color;
		}
		i++;
	}
	return (hit);
}

#endif // WORLD_UTILS_H
