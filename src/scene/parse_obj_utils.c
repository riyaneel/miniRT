/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 12:23:18 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/16 12:33:30 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/scene_parser.h"

#include "core/ctype/ft_ctype.h"
#include "core/stdlib/ft_stdlib.h"

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

void	obj_get_counts(const char *p, int *v_cnt, int *f_cnt)
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

void	obj_parse_faces(const char *p, t_mesh *m, const t_vec4 *v, int *ti)
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
