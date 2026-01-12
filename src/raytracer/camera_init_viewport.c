/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_init_viewport.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 23:32:04 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/12 20:01:29 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "raytracer/camera.h"

static const t_vec4	g_world_up = (t_vec4){{0.0f, 1.0f, 0.0f, 0.0f}};

void	camera_init_viewport(t_camera *cam, const int width, const int height)
{
	float	theta;
	float	h;
	float	viewport_w;
	float	viewport_h;
	t_vec4	w_fwd;
	t_vec4	u_right;
	t_vec4	v_up;
	t_vec4	center_to_viewport;
	t_vec4	viewport_upper_left;
	t_vec4	pixel_delta_u;
	t_vec4	pixel_delta_v;

	theta = cam->fov * (float)M_PI / 180.0f;
	h = tanf(theta / 2.0f);
	cam->aspect_ratio = (float)width / (float)height;
	viewport_h = 2.0f * h;
	viewport_w = viewport_h * cam->aspect_ratio;
	w_fwd = cam->dir;
	if ((float)fabs((double)w_fwd.y) > 0.999f)
		u_right = vec4_cross((t_vec4){{0, 0, 1, 0}}, w_fwd);
	else
		u_right = vec4_cross(g_world_up, w_fwd);
	u_right = vec4_normalize(u_right);
	v_up = vec4_cross(w_fwd, u_right);
	cam->viewport_u = vec4_scale(u_right, viewport_w);
	cam->viewport_y = vec4_scale(v_up, -viewport_h);
	center_to_viewport = w_fwd;
	viewport_upper_left = vec4_add(cam->origin, vec4_sub(center_to_viewport,
				vec4_add(vec4_scale(cam->viewport_u, 0.5f),
					vec4_scale(cam->viewport_y, 0.5f))));
	pixel_delta_u = vec4_scale(cam->viewport_u, 1.0f / (float)width);
	pixel_delta_v = vec4_scale(cam->viewport_y, 1.0f / (float)height);
	cam->viewport_u = pixel_delta_u;
	cam->viewport_y = pixel_delta_v;
	cam->pixel_00_loc = vec4_add(viewport_upper_left,
			vec4_scale(vec4_add(pixel_delta_u, pixel_delta_v), 0.5f));
}
