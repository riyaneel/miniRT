/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 08:38:46 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/02 16:17:38 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>

#include "raytracer/camera.h"
#include "raytracer/render.h"
#include "raytracer/shader.h"
#include "raytracer/world.h"
#include "utils/random_utils.h"

#ifndef SAMPLES_PER_PIXEL
# define SAMPLES_PER_PIXEL 16
#endif // SAMPLES_PER_PIXEL

static t_ray	get_sample_ray(const t_camera *cam, const int x, const int y,
		t_prng_state *rng)
{
	float	u;
	float	v;

	u = (float)x + 0.5f + (random_float(rng) - 0.5f);
	v = (float)y + 0.5f + (random_float(rng) - 0.5f);
	return (camera_get_ray(cam, u, v));
}

t_vec4	render_pixel(const t_scene *scn, const int x, const int y,
		const uint32_t seed)
{
	t_vec4			final_color;
	t_prng_state	rng;
	t_ray			r;
	t_hit			rec;
	int				s;

	final_color = (t_vec4){{0, 0, 0, 0}};
	rng = init_rng_seed((uint32_t)x, (uint32_t)y, seed);
	s = 0;
	while (s < SAMPLES_PER_PIXEL)
	{
		r = get_sample_ray(&scn->camera, x, y, &rng);
		if (hit_world(scn, &r, vec_init(0.001f, FLT_MAX, 0, 0), &rec))
			final_color = vec4_add(final_color, shade_ray(scn, &r, &rec, &rng));
		s++;
	}
	return (vec4_scale(final_color, 1.0f / (float)SAMPLES_PER_PIXEL));
}
