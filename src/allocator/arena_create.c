/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 21:25:17 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/06 16:14:57 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/mman.h>

#include "allocator/arena_allocator.h"
#include "allocator/arena_allocator_internal.h"

#ifndef MAP_ANONYMOUS
# define MAP_ANONYMOUS 0x20
#endif // #ifndef MAP_ANONYMOUS

t_arena	*arena_create(const t_arena_config config)
{
	const size_t	otd = arena_align_up(sizeof(t_arena), ARENA_DEF_ALIGN);
	size_t			total_size;
	void			*block;
	t_arena			*arena;
	uintptr_t		base_addr;

	if (__builtin_expect(config.capacity <= 0, 0))
		return (NULL);
	if (__builtin_expect((size_t)config.capacity > SIZE_MAX - otd, 0))
		return (NULL);
	total_size = otd + (size_t)config.capacity;
	block = mmap(NULL, total_size, PROT_READ | PROT_WRITE,
			MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	arena = (t_arena *)block;
	if (__builtin_expect(block == MAP_FAILED, 0))
		return (NULL);
	base_addr = (uintptr_t)((char *)block + otd);
	arena->base_ptr = base_addr;
	arena->current_ptr = base_addr;
	arena->end_ptr = base_addr + (uintptr_t)config.capacity;
	arena->total_size = total_size;
	__builtin_prefetch((void *)base_addr, 1, 3);
	return (arena);
}
