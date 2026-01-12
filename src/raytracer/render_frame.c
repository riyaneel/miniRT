/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 03:47:03 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/12 20:02:54 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytracer/camera.h"
#include "raytracer/ray_types.h"
#include "raytracer/render.h"
#include "raytracer/shader.h"
#include "raytracer/world.h"

static t_vec4	render_pixel(const t_scene *scn, const int x, const int y)
{
	const float	u = ((float)x + 0.5f);
	const float	v = ((float)y + 0.5f);
	const t_ray	r = camera_get_ray(&scn->camera, u, v);
	t_hit		rec;

	if (hit_world(scn, &r, 0.0001f, 1e30f, &rec))
		return (shade_ray(scn, &r, &rec));
	return ((t_vec4){{0, 0, 0, 0}});
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
			color = render_pixel(gfx->scene, x, y);
			idx = y * gfx->width + x;
			gfx->framebuffer->pixels[idx] = color;
			x++;
		}
		y++;
	}
}
