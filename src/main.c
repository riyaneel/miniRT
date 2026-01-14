/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:57:21 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/12 23:02:19 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "allocator/arena_allocator.h"
#include "core/rt_core.h"
#include "core/memory/ft_memory.h"
#include "graphics/graphics.h"
#include "scene/scene_parser.h"

#include "io/ft_printf.h"

#define WIN_W 1920
#define WIN_H 1080
#define MEMORY_POOL_SIZE (256 * 1024 * 1024)

__attribute__((always_inline))
static inline int	kill(const char *msg, t_arena *arena)
{
	if (msg)
		ft_dprintf(STDERR_FILENO, "%s\n", msg);
	if (arena)
		arena_destroy(arena);
	return (1);
}

int	main(const int argc, char **argv)
{
	t_arena		*arena;
	t_scene		*scene;
	t_graphics	gfx;

	arena = NULL;
	if (argc != 2)
		return (kill("Error\nUsage: ./miniRT <scene_file.rt>", arena));
	core_init();
	arena = arena_create((t_arena_config){MEMORY_POOL_SIZE});
	if (!arena)
		return (kill("Error\nFatal: Could not allocate memory arena.", arena));
	scene = scene_parse(arena, argv[1]);
	if (!scene)
		return (kill(NULL, arena));
	ft_bzero(&gfx, sizeof(t_graphics));
	if (!graphics_init(&gfx, arena, WIN_W, WIN_H))
		return (kill("Error\nFatal: Graphics initialization failed.", arena));
	gfx.scene = scene;
	graphics_setup_hooks(&gfx);
	graphics_clear(&gfx);
	mlx_loop(gfx.mlx);
	graphics_shutdown(&gfx);
	arena_destroy(arena);
	return (0);
}
