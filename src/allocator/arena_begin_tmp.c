/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_begin_tmp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 16:01:59 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/06 16:22:02 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/arena_allocator.h"

t_tmp_arena	arena_begin_tmp(t_arena *arena)
{
	t_tmp_arena	tmp_arena;

	tmp_arena.arena = arena;
	if (arena)
		tmp_arena.saved_ptr = arena->current_ptr;
	else
		tmp_arena.saved_ptr = 0;
	return (tmp_arena);
}
