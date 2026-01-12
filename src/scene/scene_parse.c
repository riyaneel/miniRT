/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 22:15:27 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/12 20:05:28 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "scene/scene_parser.h"
#include "vectors/rt_vectors.h"

#include "core/ctype/ft_ctype.h"
#include "core/memory/ft_memory.h"
#include "core/string/ft_string.h"

static bool	fill_objects(t_scene *scn, char *data)
{
	char	*p;
	int		is;
	int		ip;
	int		ic;

	is = 0;
	ip = 0;
	ic = 0;
	p = data;
	while (*p)
	{
		skip_formatting(&p);
		if (!*p)
			break ;
		if (*p == 'A' && ft_isspace(p[1]))
		{
			p++;
			scn->ambient.ratio = parse_float(&p);
			scn->ambient.color = parse_color(&p);
			scn->ambient.color = vec4_scale(scn->ambient.color,
					scn->ambient.ratio);
			scn->has_amb = true;
		}
		else if (*p == 'C' && ft_isspace(p[1]))
		{
			p++;
			scn->camera.origin = parse_vec3(&p, 1.0f);
			scn->camera.dir = vec4_normalize(parse_vec3(&p, 0.0f));
			scn->camera.fov = parse_float(&p);
			scn->has_cam = true;
		}
		else if (*p == 'L' && ft_isspace(p[1]))
		{
			p++;
			scn->light.origin = parse_vec3(&p, 1.0f);
			scn->light.ratio = parse_float(&p);
			scn->light.color = parse_color(&p);
			scn->has_light = true;
		}
		else if (!ft_strncmp(p, "sp", 2))
			parse_sphere(scn, &is, &p);
		else if (!ft_strncmp(p, "pl", 2))
			parse_plane(scn, &ip, &p);
		else if (!ft_strncmp(p, "cy", 2))
			parse_cylinder(scn, &ic, &p);
		while (*p && *p != '\n')
			p++;
		if (*p == '\n')
			p++;
	}
	return (true);
}

static void	count_objects(t_scene *scn, char *data)
{
	char	*p;

	p = data;
	while (*p)
	{
		skip_formatting(&p);
		if (!*p)
			break ;
		if (!ft_strncmp(p, "sp", 2) && ft_isspace(p[2]))
			scn->num_spheres++;
		else if (!ft_strncmp(p, "pl", 2) && ft_isspace(p[2]))
			scn->num_planes++;
		else if (!ft_strncmp(p, "cy", 2) && ft_isspace(p[2]))
			scn->num_cylinders++;
		while (*p && *p != '\n')
			p++;
		if (*p == '\n')
			p++;
	}
}

static char	*read_file_to_arena(t_arena *arena, const char *file)
{
	int		fd;
	size_t	len;
	char	*buf;
	ssize_t	bytes_read;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	len = (size_t)lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	if (len == 0)
	{
		close(fd);
		return (NULL);
	}
	buf = arena_alloc(arena, len + 1);
	if (!buf)
	{
		close(fd);
		return (NULL);
	}
	bytes_read = read(fd, buf, len);
	close(fd);
	if (bytes_read < 0)
		return (NULL);
	buf[bytes_read] = '\0';
	return (buf);
}

t_scene	*scene_parse(t_arena *arena, const char *filename)
{
	char	*data;
	t_scene	*scn;

	data = read_file_to_arena(arena, filename);
	if (!data)
	{
		printf("Error\nCannot read file '%s'\n", filename);
		return (NULL);
	}
	scn = arena_alloc(arena, sizeof(t_scene));
	if (!scn)
		return (NULL);
	ft_bzero(scn, sizeof(t_scene));
	count_objects(scn, data);
	if (scn->num_spheres)
		scn->spheres = arena_alloc_align(arena, sizeof(t_sphere)
				* (size_t)scn->num_spheres, 16);
	if (scn->num_planes)
		scn->planes = arena_alloc_align(arena, sizeof(t_plane)
				* (size_t)scn->num_planes, 16);
	if (scn->num_cylinders)
		scn->cylinders = arena_alloc_align(arena, sizeof(t_cylinder)
				* (size_t)scn->num_cylinders, 16);
	fill_objects(scn, data);
	if (!scn->has_cam || !scn->has_amb || !scn->has_light)
	{
		printf("Error\nMissing mandatory scene elements (A, C, L).\n");
		return (NULL);
	}
	printf("[Scene] Parsed OK: %d Sp, %d Pl, %d Cy\n",
		scn->num_spheres, scn->num_planes, scn->num_cylinders);
	return (scn);
}
