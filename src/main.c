/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 14:57:21 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/06 15:01:02 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "allocator/arena_allocator.h"
#include "core/rt_core.h"
#include "vectors/rt_vectors.h"

static inline bool	parse_float(const char *str, float *out)
{
	char	*end_ptr;

	*out = strtof(str, &end_ptr);
	if (str == end_ptr || *end_ptr != '\0')
		return (false);
	return (true);
}

__attribute__((noinline))
static bool	parse_args(char **argv, t_vec4 *a, t_vec4 *b)
{
	float	buffer[8];
	int		i;

	i = 0;
	while (i < 8)
	{
		if (!parse_float(argv[i + 1], &buffer[i]))
			return (false);
		i++;
	}
	__builtin_memcpy(a, &buffer[0], sizeof(t_vec4));
	__builtin_memcpy(b, &buffer[4], sizeof(t_vec4));
	return (true);
}

volatile float	g_bench_sink;

static inline void	process_silent(const t_vec4 *a, const t_vec4 *b)
{
	const t_vec4	r1 = vec4_add(*a, *b);
	const t_vec4	r2 = vec4_mul(*a, *b);
	const float		dot = vec4_dot(*a, *b);

	g_bench_sink += r1.x + r2.y + dot;
}

static void	run_malloc_bench(char **argv, const int iterations)
{
	t_vec4			data_a;
	t_vec4			data_b;
	t_vec4			*dyn_a;
	t_vec4			*dyn_b;

	if (!parse_args(argv, &data_a, &data_b))
		return ;
	const clock_t	start = clock();
	for (int k = 0; k < iterations; k++)
	{
		dyn_a = malloc(sizeof(t_vec4));
		dyn_b = malloc(sizeof(t_vec4));
		if (dyn_a && dyn_b)
		{
			*dyn_a = data_a;
			*dyn_b = data_b;
			process_silent(dyn_a, dyn_b);
		}
		free(dyn_a);
		free(dyn_b);
	}
	const double	elapsed = (double)(clock() - start) / CLOCKS_PER_SEC;
	printf("[MALLOC] Time: %.5f sec\n", elapsed);
}

static void	run_arena_bench(char **argv, const int iterations)
{
	t_vec4					data_a;
	t_vec4					data_b;
	const t_arena_config	conf = {.capacity = 1024 * 1024 * 16, .oom_policy = 0};
	t_arena					*arena = arena_create(conf);
	t_vec4					*dyn_a;
	t_vec4					*dyn_b;

	if (!arena)
	{
		printf("Arena creation failed\n");
		return ;
	}
	if (!parse_args(argv, &data_a, &data_b))
	{
		arena_destroy(arena);
		return ;
	}
	const clock_t	start = clock();
	for (int k = 0; k < iterations; k++)
	{
		dyn_a = arena_alloc(arena, sizeof(t_vec4));
		dyn_b = arena_alloc(arena, sizeof(t_vec4));
		if (dyn_a && dyn_b)
		{
			*dyn_a = data_a;
			*dyn_b = data_b;
			process_silent(dyn_a, dyn_b);
		}
		arena_reset(arena);
	}
	const double	elapsed = (double)(clock() - start) / CLOCKS_PER_SEC;
	printf("[ARENA ] Time: %.5f sec\n", elapsed);
	arena_destroy(arena);
}

int	main(const int argc, char **argv)
{
	core_init();
	if (argc != 9)
	{
		printf("Usage: %s <8 floats>\nExample: %s 1 2 3 4 5 6 7 8\n", argv[0], argv[0]);
		return (1);
	}
	printf("\n>>> STARTING BENCHMARK (10M iterations) <<<\n");
	run_malloc_bench(argv, 10000000);
	run_arena_bench(argv, 10000000);
	return (0);
}
