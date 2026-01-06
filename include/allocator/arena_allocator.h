/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_allocator.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 07:46:04 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/06 16:08:40 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_ALLOCATOR_H
# define ARENA_ALLOCATOR_H

# include "arena_allocator_types.h"

t_arena		*arena_create(t_arena_config config)
			__attribute__((warn_unused_result));

void		*arena_alloc(t_arena *arena, size_t size)
			__attribute__((warn_unused_result, malloc, alloc_size(2)));

void		*arena_alloc_align(t_arena *arena, size_t size, size_t alignment)
			__attribute__((warn_unused_result, malloc, alloc_size(2)));

void		*arena_alloc_array(t_arena *arena, size_t count, size_t size)
			__attribute__((warn_unused_result, malloc, alloc_size(2, 3)));

void		arena_reset(t_arena *arena);

void		arena_destroy(t_arena *arena);

size_t		arena_get_used(const t_arena *arena);

size_t		arena_get_capacity(const t_arena *arena);

t_tmp_arena	arena_begin_tmp(t_arena *arena);

void		arena_end_tmp(t_tmp_arena tmp);

#endif // ARENA_ALLOCATOR_H
