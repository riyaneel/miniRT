/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 21:25:17 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/06 13:46:03 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "allocator/arena_allocator.h"
#include "allocator/arena_allocator_internal.h"

t_arena	*arena_create(const t_arena_config config)
{
	const size_t	otd = arena_align_up(sizeof(t_arena), ARENA_DEF_ALIGN);
	size_t			total_size;
	void			*block;
	t_arena			*arena;
	uintptr_t		base_addr;

	if (__builtin_expect(config.capacity == 0, 0))
		return (NULL);
	if (__builtin_expect((size_t)config.capacity > SIZE_MAX - otd, 0))
		return (NULL);
	total_size = otd + (size_t)config.capacity;
	if (__builtin_expect(posix_memalign(&block, ARENA_DEF_ALIGN, total_size)
			!= 0, 0))
		return (NULL);
	arena = (t_arena *)block;
	base_addr = (uintptr_t)((char *)block + otd);
	arena->base_ptr = base_addr;
	arena->current_ptr = base_addr;
	arena->end_ptr = base_addr + (uintptr_t)config.capacity;
	arena->total_size = (size_t)config.capacity;
	__builtin_prefetch((void *)base_addr, 1, 3);
	return (arena);
}
