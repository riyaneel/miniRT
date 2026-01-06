/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_reset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 21:25:17 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/06 14:27:45 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "allocator/arena_allocator.h"

void	arena_reset(t_arena *arena)
{
	if (arena)
		arena->current_ptr = arena->base_ptr;
}
