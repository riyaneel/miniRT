/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 03:44:58 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 19:29:05 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_H
# define SHADER_H

# include "bump_mapping.h"
# include "checkerboard.h"
# include "shader_light.h"
# include "world.h"

static inline t_vec4	shade_lights(const t_scene *scn, const t_ray *r,
		const t_vec4 normal, const t_vec4 p, const t_vec4 color)
{
	t_light_calc	lc;
	t_ray			shadow;
	t_vec4			result;
	t_vec4			view;
	int				i;

	result = (t_vec4){{0, 0, 0, 0}};
	view = vec4_scale(r->dir, -1.0f);
	i = -1;
	while (++i < scn->num_lights)
	{
		lc = get_light_dir(&scn->lights[i], p);
		shadow = ray_create(vec4_add(p, vec4_scale(normal, EPSILON)), lc.dir);
		if (!hit_world_any(scn, &shadow, lc.dist - EPSILON))
		{
			result = vec4_add(result, compute_diffuse(&scn->lights[i],
						color, normal, lc.dir));
			result = vec4_add(result, compute_specular(&scn->lights[i],
						view, normal, lc.dir));
		}
	}
	return (result);
}

static inline t_vec4	shade_ray(const t_scene *scn, const t_ray *r,
		const t_hit *rec)
{
	t_vec4	color;
	t_vec4	normal;
	t_vec4	ambient;

	color = apply_checker(rec);
	normal = apply_bump(rec);
	ambient = vec4_mul(scn->ambient.color, color);
	return (vec4_add(ambient, shade_lights(scn, r, normal, rec->p, color)));
}

#endif // SHADER_H
