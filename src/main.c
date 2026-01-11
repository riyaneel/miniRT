/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:57:21 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/11 20:41:00 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/arena_allocator.h"
#include "core/rt_core.h"
#include "graphics/graphics.h"

int	main(void)
{
	const t_arena_config	arena_config = {.capacity = 64 * 1024 * 1024};
	t_arena					*arena;
	t_graphics				gfx;

	core_init();
	arena = arena_create(arena_config);
	if (!arena)
		return (1);
	__builtin_bzero(&gfx, sizeof(t_graphics));
	if (!graphics_init(&gfx, arena, 1920, 1080))
	{
		arena_destroy(arena);
		return (1);
	}
	graphics_setup_hooks(&gfx);
	mlx_loop(gfx.mlx);
	graphics_shutdown(&gfx);
	arena_destroy(arena);
	return (0);
}
