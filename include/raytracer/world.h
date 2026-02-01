/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 03:44:22 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 18:18:53 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "intersections_bvh.h"
# include "intersections_cone.h"
# include "shadow_spheres.h"
# include "world_utils.h"

static inline bool	shadow_planes(const t_scene *scn, const t_ray *r,
		const t_vec4 bounds)
{
	t_hit	tmp;
	int		i;

	i = 0;
	while (i < scn->num_planes)
	{
		if (hit_plane(&scn->planes[i], r, bounds, &tmp))
			return (true);
		i++;
	}
	return (false);
}

static inline bool	shadow_cylinders(const t_scene *scn, const t_ray *r,
		const t_vec4 bounds)
{
	t_hit	tmp;
	int		i;

	i = 0;
	while (i < scn->num_cylinders)
	{
		if (hit_cylinder(&scn->cylinders[i], r, bounds, &tmp))
			return (true);
		i++;
	}
	return (false);
}

static inline bool	shadow_cones(const t_scene *scn, const t_ray *r,
		const t_vec4 bounds)
{
	t_hit	tmp;
	int		i;

	i = 0;
	while (i < scn->num_cones)
	{
		if (hit_cone(&scn->cones[i], r, bounds, &tmp))
			return (true);
		i++;
	}
	return (false);
}

static inline bool	hit_world(const t_scene *scn, const t_ray *r,
		t_vec4 bounds, t_hit *rec)
{
	bool	hit;

	hit = false;
	if (check_spheres(scn, r, &bounds, rec))
		hit = true;
	if (check_planes(scn, r, &bounds, rec))
		hit = true;
	if (check_cylinders(scn, r, &bounds, rec))
		hit = true;
	if (check_cones(scn, r, &bounds, rec))
		hit = true;
	if (scn->num_meshes > 0)
	{
		if (check_meshes(scn, r, &bounds, rec))
			hit = true;
	}
	return (hit);
}

static inline bool	hit_world_any(const t_scene *scn, const t_ray *r,
		const float t_max)
{
	const t_vec4	bounds = {EPSILON, t_max, 0, 0};
	t_hit			dummy_rec;
	int				i;

	if (shadow_spheres(scn, r, bounds))
		return (true);
	if (shadow_planes(scn, r, bounds))
		return (true);
	if (shadow_cylinders(scn, r, bounds))
		return (true);
	if (shadow_cones(scn, r, bounds))
		return (true);
	if (scn->num_meshes > 0)
	{
		i = 0;
		while (i < scn->num_meshes)
		{
			if (hit_bvh(&scn->meshes[i], r, &dummy_rec, t_max))
				return (true);
			i++;
		}
	}
	return (false);
}

#endif // WORLD_H
