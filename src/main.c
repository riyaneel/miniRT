/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:57:21 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 12:31:01 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "allocator/arena_allocator.h"
#include "core/rt_core.h"
#include "graphics/graphics.h"
#include "scene/scene_parser.h"

#include "core/memory/ft_memory.h"
#include "core/string/ft_string.h"
#include "io/ft_printf.h"

#define WIN_W 1920
#define WIN_H 1080
#define MEMORY_POOL_SIZE (256 * 1024 * 1024)

__attribute__((always_inline))
static inline void	kill(const char *msg, t_arena *arena)
{
	if (msg)
		ft_dprintf(STDERR_FILENO, "%s\n", msg);
	if (arena)
		arena_destroy(arena);
	exit(1);
}

__attribute__((always_inline))
static inline void	check_file_extension(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		kill("Error\nFile must have .rt extension", NULL);
	if (ft_strncmp(filename + len - 3, ".rt", 3) != 0)
		kill("Error\nFile must have .rt extension", NULL);
}

int	main(const int argc, char **argv)
{
	t_arena		*arena;
	t_scene		*scene;
	t_graphics	gfx;

	arena = NULL;
	if (argc != 2)
		kill("Error\nUsage: ./miniRT <scene_file.rt>", arena);
	check_file_extension(argv[1]);
	core_init();
	arena = arena_create((t_arena_config){MEMORY_POOL_SIZE});
	if (!arena)
		kill("Error\nFatal: Could not allocate memory arena.", arena);
	scene = scene_parse(arena, argv[1]);
	if (!scene)
		kill(NULL, arena);
	ft_bzero(&gfx, sizeof(t_graphics));
	if (!graphics_init(&gfx, arena, WIN_W, WIN_H))
		kill("Error\nFatal: Graphics initialization failed.", arena);
	gfx.scene = scene;
	graphics_setup_hooks(&gfx);
	graphics_clear(&gfx);
	mlx_loop(gfx.mlx);
	graphics_shutdown(&gfx);
	arena_destroy(arena);
	return (0);
}
