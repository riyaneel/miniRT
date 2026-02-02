/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soft_shadow.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 15:10:56 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/02 16:16:09 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOFT_SHADOW_H
# define SOFT_SHADOW_H

# include "ray.h"
# include "sampling.h"
# include "soft_shadow_types.h"
# include "world.h"

static inline float	test_shadow_sample(const t_scene *scn, const t_vec4 p,
		const t_vec4 sample_pos)
{
	t_vec4	to_light;
	t_ray	shadow;
	float	dist;

	to_light = vec4_sub(sample_pos, p);
	dist = sqrtf(vec4_len_sq(to_light));
	shadow = ray_create(p, vec4_scale(to_light, 1.0f / dist));
	if (hit_world_any(scn, &shadow, dist - EPSILON))
		return (0.0f);
	return (1.0f);
}

static inline float	soft_visibility(const t_scene *scn, const t_vec4 p,
		const t_light *light, t_prng_state *rng)
{
	float	visible;
	t_vec4	to_light;
	t_vec4	sample_pos;
	int		i;

	visible = 0.0f;
	to_light = vec4_normalize(vec4_sub(light->origin, p));
	i = -1;
	while (++i < SHADOW_SAMPLES)
	{
		sample_pos = sample_disk_3d(light->origin, to_light, LIGHT_RADIUS, rng);
		visible += test_shadow_sample(scn, p, sample_pos);
	}
	return (visible * INV_SHADOW_SAMPLES);
}

#endif // SOFT_SHADOW_H
