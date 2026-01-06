/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_allocator_types.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 13:23:53 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/06 16:00:45 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_ALLOCATOR_TYPES_H
# define ARENA_ALLOCATOR_TYPES_H

# include <stddef.h>
# include <stdint.h>

# define ARENA_DEF_ALIGN 16

typedef struct s_arena_config {
	int64_t	capacity;
	int32_t	oom_policy;
	int32_t	reserved;
} __attribute__((aligned(16)))	t_arena_config;

typedef struct s_arena {
	uintptr_t	current_ptr;
	uintptr_t	end_ptr;
	uintptr_t	base_ptr;
	size_t		total_size;
} __attribute__((aligned(32)))	t_arena;

typedef struct s_tmp_arena {
	t_arena		*arena;
	uintptr_t	saved_ptr;
} __attribute__((aligned(16)))	t_tmp_arena;

#endif // ARENA_ALLOCATOR_TYPES_H
