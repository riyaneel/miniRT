/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_alloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 21:25:17 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/06 14:32:05 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/arena_allocator.h"

void	*arena_alloc(t_arena *arena, const size_t size)
{
	return (arena_alloc_align(arena, size, ARENA_DEF_ALIGN));
}
