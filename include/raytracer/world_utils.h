/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 17:59:16 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 18:11:18 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_UTILS_H
# define WORLD_UTILS_H

# include "check_spheres.h"
# include "intersections.h"
# include "intersections_cylinder.h"
# include "scene/scene_types.h"

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
			rec->type = HIT_PLANE;
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
			rec->type = HIT_CYLINDER;
			rec->obj_center = scn->cylinders[i].center;
			rec->obj_axis = scn->cylinders[i].axis;
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
			rec->type = HIT_MESH;
		}
		i++;
	}
	return (hit);
}

static inline bool	check_cones(const t_scene *scn, const t_ray *r,
		t_vec4 *bounds, t_hit *rec)
{
	t_hit	tmp;
	bool	hit;
	int		i;

	hit = false;
	i = 0;
	while (i < scn->num_cones)
	{
		if (hit_cone(&scn->cones[i], r, *bounds, &tmp))
		{
			hit = true;
			bounds->y = tmp.t;
			*rec = tmp;
			rec->color_obj = scn->cones[i].color;
			rec->type = HIT_CONE;
			rec->obj_center = scn->cones[i].apex;
			rec->obj_axis = scn->cones[i].axis;
		}
		i++;
	}
	return (hit);
}

#endif // WORLD_UTILS_H
