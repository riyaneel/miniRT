/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 03:44:58 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/12 20:12:26 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_H
# define SHADER_H

# include "raytracer/world.h"
# include "utils/maths_utils.h"

static inline t_vec4	shade_ray(const t_scene *scn, const t_ray *r, const t_hit *rec)
{
	t_vec4	ambient;
	t_vec4	diffuse;
	t_vec4	specular;
	t_vec4	light_dir;
	t_vec4	view_dir;
	t_vec4	reflect_dir;
	float	light_dist;
	float	diff_strength;
	float	spec_strength;
	t_ray	shadow_ray;
	t_vec4	light_vec;

	ambient = vec4_mul(scn->ambient.color, rec->color_obj);
	ambient = vec4_scale(ambient, scn->ambient.ratio);
	light_vec = vec4_sub(scn->light.origin, rec->p);
	light_dist = sqrtf(vec4_len_sq(light_vec));
	light_dir = vec4_scale(light_vec, 1.0f / light_dist);
	shadow_ray = ray_create(vec4_add(rec->p, vec4_scale(rec->normal, EPSILON)),
			light_dir);
	if (hit_world_any(scn, &shadow_ray, light_dist - EPSILON))
		return (ambient);
	diff_strength = fmax_fast(vec4_dot(rec->normal, light_dir), 0.0f);
	diffuse = vec4_mul(scn->light.color, rec->color_obj);
	diffuse = vec4_scale(diffuse, scn->light.ratio * diff_strength);
	view_dir = vec4_scale(r->dir, -1.0f);
	reflect_dir = vec4_sub(vec4_scale(rec->normal, 2.0f * vec4_dot(rec->normal,
					light_dir)), light_dir);
	spec_strength = powf(fmax_fast(vec4_dot(view_dir, reflect_dir), 0.0f),
			32.0f);
	specular = vec4_scale(scn->light.color, scn->light.ratio * spec_strength
			* 0.6f);
	return (vec4_add(ambient, vec4_add(diffuse, specular)));
}

#endif // SHADER_H
