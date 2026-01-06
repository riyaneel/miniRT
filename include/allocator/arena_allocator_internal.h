/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_allocator_internal.h                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 17:04:56 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/06 13:51:03 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_ALLOCATOR_INTERNAL_H
# define ARENA_ALLOCATOR_INTERNAL_H

# include "arena_allocator_types.h"

static inline size_t	arena_align_up(const size_t num, const size_t align)
{
	return ((num + (align - 1)) & ~(align - 1));
}

static inline bool	arena_internal_has_space(const t_arena *arena,
		const size_t size, const size_t align)
{
	const uintptr_t	current = arena->current_ptr;
	const uintptr_t	next_aligned = arena_align_up(current, align);

	return ((next_aligned + size) <= arena->end_ptr);
}

#endif // ARENA_ALLOCATOR_INTERNAL_H
