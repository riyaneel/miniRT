/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 23:23:39 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/11 23:31:36 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "ray.h"
# include "scene/scene_types.h"
# include "vectors/rt_vectors.h"

void	camera_init_viewport(t_camera *cam, int width, int height);

static inline t_ray	camera_get_ray(const t_camera *camera, const float u,
		const float v)
{
	t_vec4	target;
	t_vec4	ray_dir;

	target = vec4_add(camera->pixel_00_loc,
			vec4_add(vec4_scale(camera->viewport_u, u),
				vec4_scale(camera->viewport_y, v)));
	ray_dir = vec4_sub(target, camera->origin);
	ray_dir = vec4_normalize(ray_dir);
	return (ray_create(camera->origin, ray_dir));
}

#endif // CAMERA_H
