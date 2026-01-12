/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 03:47:03 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/12 20:16:43 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer/camera.h"
#include "raytracer/render.h"
#include "raytracer/shader.h"
#include "raytracer/world.h"
#include "utils/random_utils.h"

#define SAMPLES_PER_PIXEL 10

static t_vec4	render_pixel(const t_scene *scn, const int x, const int y,
		const uint32_t frame_seed)
{
	t_vec4			final_color = (t_vec4){{0,0,0,0}};
	t_prng_state	rng;
	int				s;

	rng = init_rng_seed((uint32_t)x, (uint32_t)y, frame_seed);
	s = 0;
	while (s < SAMPLES_PER_PIXEL)
	{
		float u_offset = random_float(&rng) - 0.5f;
		float v_offset = random_float(&rng) - 0.5f;
		float u = ((float)x + 0.5f + u_offset);
		float v = ((float)y + 0.5f + v_offset);
		t_ray r = camera_get_ray(&scn->camera, u, v);
		t_hit rec;
		if (hit_world(scn, &r, 0.001f, 1e30f, &rec))
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
