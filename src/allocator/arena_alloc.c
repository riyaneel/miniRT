/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_alloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 21:25:17 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/06 16:12:49 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/arena_allocator.h"

#if defined (DEBUG) || defined(__SANITIZE_ADDRESS__)
# include <sanitizer/asan_interface.h>

void	*arena_alloc(t_arena *arena, const size_t size)
{
	void	*ptr;

	ptr = arena_alloc_align(arena, size, ARENA_DEF_ALIGN);
	if (ptr)
		ASAN_UNPOISON_MEMORY_REGION(ptr, size);
	return (ptr);
}
#else // #if defined (DEBUG) || defined(__SANITIZE_ADDRESS__)

void	*arena_alloc(t_arena *arena, const size_t size)
{
	return (arena_alloc_align(arena, size, ARENA_DEF_ALIGN));
}
#endif  // #if defined (DEBUG) || defined(__SANITIZE_ADDRESS__) #else
