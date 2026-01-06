/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_allocator_internal.h                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 17:04:56 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/06 14:38:21 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_ALLOCATOR_INTERNAL_H
# define ARENA_ALLOCATOR_INTERNAL_H

static inline size_t	arena_align_up(const size_t num, const size_t align)
{
	return ((num + (align - 1)) & ~(align - 1));
}

#endif // ARENA_ALLOCATOR_INTERNAL_H
