/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 03:44:58 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 17:48:17 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_H
# define SHADER_H

# include "checkerboard.h"
# include "shader_light.h"
# include "world.h"

static inline t_vec4	shade_single_light(const t_scene *scn, const t_ray *r,
		const t_hit *rec, const t_vec4 color)
{
	t_light_calc	lc;
	t_ray			shadow_ray;
	int				i;
	t_vec4			result;

	result = (t_vec4){{0, 0, 0, 0}};
	i = 0;
	while (i < scn->num_lights)
	{
		lc = get_light_dir(&scn->lights[i], rec->p);
		shadow_ray = ray_create(vec4_add(rec->p,
					vec4_scale(rec->normal, EPSILON)), lc.dir);
		if (!hit_world_any(scn, &shadow_ray, lc.dist - EPSILON))
		{
			result = vec4_add(result,
					compute_diffuse_light(&scn->lights[i], color, rec, lc.dir));
			result = vec4_add(result,
					compute_specular_light(&scn->lights[i], r, rec, lc.dir));
		}
		i++;
	}
	return (result);
}

static inline t_vec4	shade_ray(const t_scene *scn, const t_ray *r,
		const t_hit *rec)
{
	t_vec4	color;
	t_vec4	ambient;

	color = apply_checker(rec);
	ambient = vec4_scale(vec4_mul(scn->ambient.color, color),
			scn->ambient.ratio);
	return (vec4_add(ambient, shade_single_light(scn, r, rec, color)));
}

#endif // SHADER_H
