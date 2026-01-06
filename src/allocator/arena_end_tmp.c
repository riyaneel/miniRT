/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_end_tmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:01:59 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/06 16:27:49 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/arena_allocator.h"

#if defined (DEBUG) || defined(__SANITIZE_ADDRESS__)
# include <sanitizer/asan_interface.h>

void	arena_end_tmp(const t_tmp_arena tmp)
{
	size_t	size_to_poison;

	if (!tmp.arena)
		return ;
	if (tmp.arena->current_ptr > tmp.saved_ptr)
	{
		size_to_poison = tmp.arena->current_ptr - tmp.saved_ptr;
		ASAN_POISON_MEMORY_REGION((void *)tmp.saved_ptr, size_to_poison);
	}
	tmp.arena->current_ptr = tmp.saved_ptr;
}
#else // #if defined (DEBUG) || defined(__SANITIZE_ADDRESS__)

void	arena_end_tmp(const t_tmp_arena tmp)
{
	if (!tmp.arena)
		return ;
	tmp.arena->current_ptr = tmp.saved_ptr;
}
#endif  // #if defined (DEBUG) || defined(__SANITIZE_ADDRESS__) #else
