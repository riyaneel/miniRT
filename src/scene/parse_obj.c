/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 09:48:30 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/17 13:44:29 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/mesh_types.h"
#include "scene/scene_parser.h"
#include "utils/maths_utils.h"

static void	normalize_mesh(const t_mesh *m)
{
	t_vec4	range[3];
	float	scale;
	int		i;

	range[0] = (t_vec4){{FLT_MAX, FLT_MAX, FLT_MAX, 1}};
	range[1] = (t_vec4){{-FLT_MAX, -FLT_MAX, -FLT_MAX, 1}};
	i = -1;
	while (++i < m->num_tris)
	{
		range[0] = vec4_min(range[0], m->tris[i].v0);
		range[1] = vec4_max(range[1], m->tris[i].v0);
	}
	range[2] = vec4_sub(range[1], range[0]);
	scale = fmax_fast(range[2].y, range[2].z);
	scale = 4.0f / fmax_fast(range[2].x, scale);
	range[0] = vec4_add(range[0], vec4_scale(range[2], 0.5f));
	i = -1;
	while (++i < m->num_tris)
	{
		m->tris[i].v0 = vec4_scale(vec4_sub(m->tris[i].v0, range[0]), scale);
		m->tris[i].e1 = vec4_scale(m->tris[i].e1, scale);
		m->tris[i].e2 = vec4_scale(m->tris[i].e2, scale);
	}
}

static void	parse_data(char *d, t_mesh *m, t_vec4 *vs, int *c)
{
	c[2] = 1;
	c[3] = 0;
	while (*d)
	{
		if (d[0] == 'v' && d[1] == ' ' && ++d && ++d)
			vs[c[2]++] = parse_vec3(&d, 1.0f);
		else if (d[0] == 'f' && d[1] == ' ')
			obj_parse_faces(d, m, vs, &c[3]);
		while (*d && *d != '\n')
			d++;
		if (*d)
			d++;
	}
}

t_mesh	*parse_obj(t_arena *arena, const char *filename)
{
	char	*d;
	t_mesh	*m;
	t_vec4	*vs;
	int		c[4];

	d = read_file_to_arena(arena, filename);
	if (!d)
		return (NULL);
	obj_get_counts(d, &c[0], &c[1]);
	m = arena_alloc(arena, sizeof(t_mesh));
	vs = arena_alloc_array(arena, (size_t)c[0] + 1, sizeof(t_vec4));
	if (m)
		m->tris = arena_alloc_array(arena, (size_t)c[1], sizeof(t_triangle));
	if (!m || !vs || !m->tris)
		return (NULL);
	m->num_tris = c[1];
	parse_data(d, m, vs, c);
	normalize_mesh(m);
	return (m);
}

void	mesh_apply_transform(const t_mesh *m, const t_vec4 pos,
			const float scale)
{
	int	i;

	i = 0;
	while (i < m->num_tris)
	{
		m->tris[i].v0 = vec4_scale(m->tris[i].v0, scale);
		m->tris[i].e1 = vec4_scale(m->tris[i].e1, scale);
		m->tris[i].e2 = vec4_scale(m->tris[i].e2, scale);
		m->tris[i].v0 = vec4_add(m->tris[i].v0, pos);
		i++;
	}
}
