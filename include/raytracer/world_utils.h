/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:59:16 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/17 12:34:35 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_UTILS_H
# define WORLD_UTILS_H

# include "raytracer/intersections.h"
# include "raytracer/intersections_cylinder.h"
# include "scene/scene_types.h"

static inline bool	check_spheres(const t_scene *scn, const t_ray *r,
		t_vec4 *bounds, t_hit *rec)
{
	t_hit	tmp;
	bool	hit;
	int		i;

	hit = false;
	i = 0;
	while (i < scn->num_spheres)
	{
		if (hit_sphere(&scn->spheres[i], r, *bounds, &tmp))
		{
			hit = true;
			bounds->y = tmp.t;
			*rec = tmp;
			rec->color_obj = scn->spheres[i].color;
		}
		i++;
	}
	return (hit);
}

static inline bool	check_planes(const t_scene *scn, const t_ray *r,
		t_vec4 *bounds, t_hit *rec)
{
	t_hit	tmp;
	bool	hit;
	int		i;

	hit = false;
	i = 0;
	while (i < scn->num_planes)
	{
		if (hit_plane(&scn->planes[i], r, *bounds, &tmp))
		{
			hit = true;
			bounds->y = tmp.t;
			*rec = tmp;
			rec->color_obj = scn->planes[i].color;
		}
		i++;
	}
	return (hit);
}

static inline bool	check_cylinders(const t_scene *scn, const t_ray *r,
		t_vec4 *bounds, t_hit *rec)
{
	t_hit	tmp;
	bool	hit;
	int		i;

	hit = false;
	i = 0;
	while (i < scn->num_cylinders)
	{
		if (hit_cylinder(&scn->cylinders[i], r, *bounds, &tmp))
		{
			hit = true;
			bounds->y = tmp.t;
			*rec = tmp;
			rec->color_obj = scn->cylinders[i].color;
		}
		i++;
	}
	return (hit);
}

static inline bool	check_meshes(const t_scene *scn, const t_ray *r,
		t_vec4 *bounds, t_hit *rec)
{
	bool	hit;
	int		i;

	hit = false;
	i = 0;
	while (i < scn->num_meshes)
	{
		if (hit_bvh(&scn->meshes[i], r, rec, bounds->y))
		{
			hit = true;
			bounds->y = rec->t;
			rec->color_obj = scn->meshes[i].color;
		}
		i++;
	}
	return (hit);
}

#endif // WORLD_UTILS_H
