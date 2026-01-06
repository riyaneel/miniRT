/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_get_used.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 21:25:17 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/06 14:33:56 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/arena_allocator.h"

size_t	arena_get_used(const t_arena *arena)
{
	if (!arena)
		return (0);
	return (arena->current_ptr - arena->base_ptr);
}

size_t	arena_get_capacity(const t_arena *arena)
{
	if (!arena)
		return (0);
	return (arena->total_size);
}
