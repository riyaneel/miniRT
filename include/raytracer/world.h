/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 03:44:22 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/12 19:55:11 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "raytracer/intersections.h"
# include "raytracer/intersections_cylinder.h"
# include "scene/scene_types.h"

static inline bool	hit_world(const t_scene *scn, const t_ray *r,
		float t_min, float t_max, t_hit *rec)
{
	t_hit	temp_rec;
	bool	hit_anything;
	float	closest_so_far;
	int		i;

	hit_anything = false;
	closest_so_far = t_max;
	i = 0;
	while (i < scn->num_spheres)
	{
		if (hit_sphere(&scn->spheres[i], r, t_min, closest_so_far, &temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
			rec->color_obj = scn->spheres[i].color;
		}
		i++;
	}
	i = 0;
	while (i < scn->num_planes)
	{
		if (hit_plane(&scn->planes[i], r, t_min, closest_so_far, &temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
			rec->color_obj = scn->planes[i].color;
		}
		i++;
	}
	i = 0;
	while (i < scn->num_cylinders)
	{
		if (hit_cylinder(&scn->cylinders[i], r, t_min,
				closest_so_far, &temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t;
			*rec = temp_rec;
			rec->color_obj = scn->cylinders[i].color;
		}
		i++;
	}
	return (hit_anything);
}

static inline bool	hit_world_any(const t_scene *scn, const t_ray *r,
		float t_max)
{
	const float	t_min = EPSILON;
	t_hit		temp_rec;
	int			i;

	i = 0;
	while (i < scn->num_spheres)
	{
		if (hit_sphere(&scn->spheres[i], r, t_min, t_max, &temp_rec))
			return (true);
		i++;
	}
	i = 0;
	while (i < scn->num_planes)
	{
		if (hit_plane(&scn->planes[i], r, t_min, t_max, &temp_rec))
			return (true);
		i++;
	}
	i = 0;
	while (i < scn->num_cylinders)
	{
		if (hit_cylinder(&scn->cylinders[i], r, t_min, t_max, &temp_rec))
			return (true);
		i++;
	}
	return (false);
}

#endif // WORLD_H
