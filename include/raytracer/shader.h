/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 03:44:58 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/16 08:08:51 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_H
# define SHADER_H

# include "world.h"
# include "utils/maths_utils.h"

typedef struct s_light_calc {
	t_vec4	dir;
	float	dist;
	float	padding[3];
}	t_light_calc;

static inline t_light_calc	get_light_calc(const t_scene *scn, const t_vec4 p)
{
	t_light_calc	lc;
	t_vec4			lv;

	lv = vec4_sub(scn->light.origin, p);
	lc.dist = sqrtf(vec4_len_sq(lv));
	lc.dir = vec4_scale(lv, 1.0f / lc.dist);
	return (lc);
}

static inline t_vec4	compute_diffuse(const t_scene *scn, const t_hit *rec,
		const t_vec4 light_dir)
{
	float	diff_strength;
	t_vec4	diffuse;

	diff_strength = fmax_fast(vec4_dot(rec->normal, light_dir), 0.0f);
	diffuse = vec4_mul(scn->light.color, rec->color_obj);
	return (vec4_scale(diffuse, scn->light.ratio * diff_strength));
}

static inline t_vec4	compute_specular(const t_scene *scn, const t_ray *r,
		const t_hit *rec, const t_vec4 light_dir)
{
	t_vec4	view_dir;
	t_vec4	reflect_dir;
	float	spec_strength;

	view_dir = vec4_scale(r->dir, -1.0f);
	reflect_dir = vec4_sub(vec4_scale(rec->normal, 2.0f * vec4_dot(rec->normal,
					light_dir)), light_dir);
	spec_strength = powf(fmax_fast(vec4_dot(view_dir, reflect_dir), 0.0f),
			32.0f);
	return (vec4_scale(scn->light.color, scn->light.ratio
			* spec_strength * 0.6f));
}

static inline t_vec4	shade_ray(const t_scene *scn, const t_ray *r,
		const t_hit *rec)
{
	t_vec4			ambient;
	t_light_calc	lc;
	t_ray			shadow_ray;
	t_vec4			phong;

	ambient = vec4_scale(vec4_mul(scn->ambient.color, rec->color_obj),
			scn->ambient.ratio);
	lc = get_light_calc(scn, rec->p);
	shadow_ray = ray_create(vec4_add(rec->p,
				vec4_scale(rec->normal, EPSILON)), lc.dir);
	if (hit_world_any(scn, &shadow_ray, lc.dist - EPSILON))
		return (ambient);
	phong = vec4_add(compute_diffuse(scn, rec, lc.dir),
			compute_specular(scn, r, rec, lc.dir));
	return (vec4_add(ambient, phong));
}

#endif // SHADER_H
