/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 03:47:03 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/14 18:32:10 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>

#include "raytracer/camera.h"
#include "raytracer/render.h"
#include "raytracer/shader.h"
#include "raytracer/world.h"
#include "utils/random_utils.h"

#define SAMPLES_PER_PIXEL 10

static t_ray	get_sample_ray(const t_camera *cam, const int x, const int y,
		t_prng_state *rng)
{
	float	u;
	float	v;

	u = (float)x + 0.5f + (random_float(rng) - 0.5f);
	v = (float)y + 0.5f + (random_float(rng) - 0.5f);
	return (camera_get_ray(cam, u, v));
}

static t_vec4	render_pixel(const t_scene *scn, const int x, const int y,
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
			final_color = vec4_add(final_color, shade_ray(scn, &r, &rec));
		s++;
	}
	return (vec4_scale(final_color, 1.0f / (float)SAMPLES_PER_PIXEL));
}

void	render_frame(const t_graphics *gfx)
{
	int		x;
	int		y;
	t_vec4	color;
	int		idx;

	camera_init_viewport(&gfx->scene->camera, gfx->width, gfx->height);
	y = 0;
	while (y < gfx->height)
	{
		x = 0;
		while (x < gfx->width)
		{
			color = render_pixel(gfx->scene, x, y, 1);
			idx = y * gfx->width + x;
			gfx->framebuffer->pixels[idx] = color;
			x++;
		}
		y++;
	}
}
