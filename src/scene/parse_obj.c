/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 09:48:30 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/16 11:50:24 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core/ctype/ft_ctype.h"
#include "core/stdlib/ft_stdlib.h"

#include "scene/mesh_types.h"
#include "scene/scene_parser.h"
#include "utils/maths_utils.h"

static void	normalize_mesh(const t_mesh *m)
{
	t_vec4	min_max[3];
	float	scale;
	int		i;

	min_max[0] = (t_vec4){{FLT_MAX, FLT_MAX, FLT_MAX, 1}};
	min_max[1] = (t_vec4){{-FLT_MAX, -FLT_MAX, -FLT_MAX, 1}};
	i = -1;
	while (++i < m->num_tris)
	{
		min_max[0] = vec4_min(min_max[0], m->tris[i].v0);
		min_max[1] = vec4_max(min_max[1], m->tris[i].v0);
	}
	min_max[2] = vec4_sub(min_max[1], min_max[0]);
	scale = 4.0f / fmax_fast(min_max[2].x, fmax_fast(min_max[2].y, min_max[2].z));
	min_max[0] = vec4_add(min_max[0], vec4_scale(min_max[2], 0.5f));
	i = -1;
	while (++i < m->num_tris)
	{
		m->tris[i].v0 = vec4_scale(vec4_sub(m->tris[i].v0, min_max[0]), scale);
		m->tris[i].e1 = vec4_scale(m->tris[i].e1, scale);
		m->tris[i].e2 = vec4_scale(m->tris[i].e2, scale);
	}
}

static int	count_indices(const char *p)
{
	int	n;

	n = 0;
	while (*p && *p != '\n')
	{
		while (*p && ft_isspace(*p) && *p != '\n')
			p++;
		if (!*p || *p == '\n')
			break ;
		n++;
		while (*p && !ft_isspace(*p) && *p != '\n')
			p++;
	}
	return (n);
}

static void	get_counts(const char *p, int *v_cnt, int *f_cnt)
{
	int	n;

	*v_cnt = 0;
	*f_cnt = 0;
	while (*p)
	{
		if (p[0] == 'v' && p[1] == ' ')
			(*v_cnt)++;
		else if (p[0] == 'f' && p[1] == ' ')
		{
			n = count_indices(p + 2);
			if (n == 3)
				(*f_cnt)++;
			else if (n == 4)
				(*f_cnt) += 2;
		}
		while (*p && *p != '\n')
			p++;
		if (*p)
			p++;
	}
}

static void	add_tri(const t_mesh *m, int *ti, const t_vec4 *v, const int *idx)
{
	t_triangle	*t;

	t = &m->tris[(*ti)++];
	t->v0 = v[idx[0]];
	t->e1 = vec4_sub(v[idx[1]], v[idx[0]]);
	t->e2 = vec4_sub(v[idx[2]], v[idx[0]]);
	t->normal = vec4_normalize(vec4_cross(t->e1, t->e2));
}

static void	parse_faces(const char *p, t_mesh *m, const t_vec4 *v, int *ti)
{
	int	idx[4];
	int	i;

	i = 0;
	p += 2;
	while (i < 4 && *p && *p != '\n')
	{
		while (*p && ft_isspace(*p))
			p++;
		if (*p >= '0' && *p <= '9')
			idx[i++] = ft_atoi(p);
		else
			break ;
		while (*p && !ft_isspace(*p) && *p != '\n')
			p++;
	}
	if (i >= 3)
		add_tri(m, ti, v, (int []){idx[0], idx[1], idx[2]});
	if (i == 4)
		add_tri(m, ti, v, (int []){idx[0], idx[2], idx[3]});
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
	get_counts(d, &c[0], &c[1]);
	m = arena_alloc(arena, sizeof(t_mesh));
	vs = arena_alloc_array(arena, (size_t)c[0] + 1, sizeof(t_vec4));
	m->tris = arena_alloc_array(arena, (size_t)c[1], sizeof(t_triangle));
	if (!m || !vs || !m->tris)
		return (NULL);
	m->num_tris = c[1];
	c[2] = 1;
	c[3] = 0;
	while (*d)
	{
		if (d[0] == 'v' && d[1] == ' ' && (d += 2))
			vs[c[2]++] = parse_vec3(&d, 1.0f);
		else if (d[0] == 'f' && d[1] == ' ')
			parse_faces(d, m, vs, &c[3]);
		while (*d && *d++ != '\n')
			;
	}
	normalize_mesh(m);
	return (m);
}
