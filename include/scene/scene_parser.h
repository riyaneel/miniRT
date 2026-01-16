/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:43:22 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/16 08:16:52 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_PARSER_H
# define SCENE_PARSER_H

# include "scene_types.h"
# include "allocator/arena_allocator.h"

void	skip_formatting(char **p);

float	parse_float(char **p);

t_vec4	parse_vec3(char **p, float w);

t_vec4	parse_color(char **p);

void	parse_sphere(const t_scene *scn, int *idx, char **p);

void	parse_plane(const t_scene *scn, int *idx, char **p);

void	parse_cylinder(t_scene *scn, int *idx, char **p);

char	*read_file_to_arena(t_arena *arena, const char *file);

void	count_objects(t_scene *scn, char *data);

bool	fill_objects(t_scene *scn, char *data);

t_scene	*scene_parse(t_arena *arena, const char *filename);

#endif // SCENE_PARSER_H
