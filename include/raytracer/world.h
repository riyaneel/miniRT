/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 03:44:22 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/14 18:02:26 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

# include "world_utils.h"

static inline bool	shadow_spheres(const t_scene *scn, const t_ray *r,
		const t_vec4 bounds)
{
	t_hit	tmp;
	int		i;

	i = 0;
	while (i < scn->num_spheres)
	{
		if (hit_sphere(&scn->spheres[i], r, bounds, &tmp))
			return (true);
		i++;
	}
	return (false);
}

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
	return (hit);
}

static inline bool	hit_world_any(const t_scene *scn, const t_ray *r,
		const float t_max)
{
	const t_vec4	bounds = {EPSILON, t_max, 0, 0};

	if (shadow_spheres(scn, r, bounds))
		return (true);
	if (shadow_planes(scn, r, bounds))
		return (true);
	if (shadow_cylinders(scn, r, bounds))
		return (true);
	return (false);
}

#endif // WORLD_H
