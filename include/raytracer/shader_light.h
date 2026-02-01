/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader_light.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 17:46:46 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 19:36:04 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_LIGHT_H
# define SHADER_LIGHT_H

# include "ray.h"
# include "scene/scene_types.h"
# include "utils/maths_utils.h"

typedef struct s_light_calc
{
	t_vec4	dir;
	float	dist;
	float	padding[3];
}	t_light_calc;

static inline t_light_calc	get_light_dir(const t_light *light, const t_vec4 p)
{
	t_light_calc	lc;
	t_vec4			lv;

	lv = vec4_sub(light->origin, p);
	lc.dist = sqrtf(vec4_len_sq(lv));
	lc.dir = vec4_scale(lv, 1.0f / lc.dist);
	return (lc);
}

static inline t_vec4	compute_diffuse(const t_light *light, const t_vec4 color,
		const t_vec4 normal, const t_vec4 light_dir)
{
	float	diff;

	diff = fmax_fast(vec4_dot(normal, light_dir), 0.0f);
	return (vec4_scale(vec4_mul(light->color, color), light->ratio * diff));
}

static inline t_vec4	compute_specular(const t_light *light, const t_vec4 view,
		const t_vec4 normal, const t_vec4 light_dir)
{
	t_vec4	reflect_dir;
	float	spec;

	reflect_dir = vec4_sub(vec4_scale(normal,
				2.0f * vec4_dot(normal, light_dir)), light_dir);
	spec = powf(fmax_fast(vec4_dot(view, reflect_dir), 0.0f), 32.0f);
	return (vec4_scale(light->color, light->ratio * spec * 0.6f));
}

#endif // SHADER_LIGHT_H
