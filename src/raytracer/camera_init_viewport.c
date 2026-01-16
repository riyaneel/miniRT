/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_init_viewport.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 23:32:04 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/16 08:12:45 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "raytracer/camera.h"

static const t_vec4	g_world_up = (t_vec4){{0.0f, 1.0f, 0.0f, 0.0f}};

static t_vec4	get_camera_right(const t_vec4 dir)
{
	t_vec4	u_right;

	if (fabsf(dir.y) > 0.999f)
		u_right = vec4_cross((t_vec4){{0, 0, 1, 0}}, dir);
	else
		u_right = vec4_cross(g_world_up, dir);
	return (vec4_normalize(u_right));
}

static void	init_viewport_dims(t_camera *cam, const int width, const int height)
{
	float	half_h;
	float	vp_h;
	float	vp_w;
	t_vec4	u;
	t_vec4	v;

	half_h = tanf((cam->fov * (float)M_PI / 180.0f) * 0.5f);
	cam->aspect_ratio = (float)width / (float)height;
	vp_h = 2.0f * half_h;
	vp_w = vp_h * cam->aspect_ratio;
	u = get_camera_right(cam->dir);
	v = vec4_cross(cam->dir, u);
	cam->viewport_u = vec4_scale(u, vp_w);
	cam->viewport_y = vec4_scale(v, -vp_h);
}

void	camera_init_viewport(t_camera *cam, const int width, const int height)
{
	t_vec4	d_u;
	t_vec4	d_v;
	t_vec4	upper_left;
	t_vec4	center;

	init_viewport_dims(cam, width, height);
	d_u = vec4_scale(cam->viewport_u, 1.0f / (float)width);
	d_v = vec4_scale(cam->viewport_y, 1.0f / (float)height);
	center = vec4_add(cam->origin, cam->dir);
	upper_left = vec4_sub(center, vec4_scale(vec4_add(cam->viewport_u,
					cam->viewport_y), 0.5f));
	cam->pixel_00_loc = vec4_add(upper_left, vec4_scale(vec4_add(d_u, d_v),
				0.5f));
	cam->viewport_u = d_u;
	cam->viewport_y = d_v;
}
