/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_alloc_align.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 21:25:17 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/06 14:31:43 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/arena_allocator.h"

void	*arena_alloc_align(t_arena *arena, const size_t size,
			const size_t alignment)
{
	uintptr_t	current;
	uintptr_t	aligned_ptr;
	uintptr_t	next_ptr;

	if (__builtin_expect((alignment & (alignment - 1)) != 0, 0))
		return (NULL);
	current = arena->current_ptr;
	aligned_ptr = (current + (alignment - 1)) & ~(alignment - 1);
	next_ptr = aligned_ptr + size;
	if (__builtin_expect(next_ptr <= arena->end_ptr, 1))
	{
		arena->current_ptr = next_ptr;
		return ((void *)aligned_ptr);
	}
	return (NULL);
}
