/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_mesh.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 13:22:22 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 13:31:03 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/scene_parser.h"

#include "core/ctype/ft_ctype.h"
#include "core/string/ft_string.h"
#include "io/ft_printf.h"

static void	init_mesh_instance(t_mesh *dst, const t_mesh *src, char **p)
{
	t_vec4	pos;
	float	scale;

	*dst = *src;
	pos = (t_vec4){{0, 0, 0, 1}};
	scale = 1.0f;
	skip_formatting(p);
	if (**p && (**p == '-' || ft_isdigit(**p)))
		pos = parse_vec3(p, 1.0f);
	skip_formatting(p);
	if (**p && (**p == '-' || ft_isdigit(**p)))
		scale = parse_float(p);
	skip_formatting(p);
	if (**p && (**p == '-' || ft_isdigit(**p)))
		dst->color = parse_color(p);
	else
		dst->color = (t_vec4){{0.57f, 0.77f, 0.44f, 1.0f}};
	mesh_apply_transform(dst, pos, scale);
}

static int	extract_mesh_path(char **p, char *path)
{
	int	i;

	i = 0;
	while (**p && **p != '\n' && !ft_isspace(**p) && i < 255)
		path[i++] = *(*p)++;
	path[i] = '\0';
	return (i);
}

static void	load_single_mesh(const t_scene *scn, t_arena *arena, char **p,
		int *idx)
{
	char	path[256];
	t_mesh	*tmp;

	(*p) += 3;
	skip_formatting(p);
	extract_mesh_path(p, path);
	ft_printf("[Mesh %d] Loading '%s'...\n", *idx, path);
	tmp = parse_obj(arena, path);
	if (tmp)
	{
		init_mesh_instance(&scn->meshes[*idx], tmp, p);
		build_bvh(&scn->meshes[*idx], arena);
		(*idx)++;
	}
}

void	load_meshes(const t_scene *scn, t_arena *arena, char *p)
{
	int	idx;

	idx = 0;
	while (*p)
	{
		skip_formatting(&p);
		if (ft_strncmp(p, "obj", 3) == 0 && ft_isspace(p[3]))
			load_single_mesh(scn, arena, &p, &idx);
		while (*p && *p != '\n')
			p++;
		if (*p)
			p++;
	}
}
