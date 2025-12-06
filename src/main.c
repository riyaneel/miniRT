/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:42:42 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/12/06 07:19:29 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "rt_vectors.h"

static inline bool	parse_float(const char *str, float *out)
{
	char	*end_ptr;

	*out = strtof(str, &end_ptr);
	if (str == end_ptr || *end_ptr != '\0')
		return (false);
	return (true);
}

__attribute__((noinline))
static bool	parse_args(const int argc, char **argv, t_vec4 *a, t_vec4 *b)
{
	float	buffer[8];
	int		i;

	if (argc != 9)
		return (false);
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

static void	process_operations(const t_vec4 a, const t_vec4 b)
{
	const t_vec4	add_v = vec4_add(a, b);
	const t_vec4	sub_v = vec4_sub(a, b);
	const t_vec4	mul_v = vec4_mul(a, b);
	const t_vec4	div_v = vec4_div(a, b);

	__asm__ volatile ("" ::: "memory");
	printf("AddVec -> a -> %.2f, b -> %.2f, c -> %.2f, d -> %.2f\n",
		(double)add_v.x, (double)add_v.y, (double)add_v.z, (double)add_v.w);
	printf("SubVec -> a -> %.2f, b -> %.2f, c -> %.2f, d -> %.2f\n",
		(double)sub_v.x, (double)sub_v.y, (double)sub_v.z, (double)sub_v.w);
	printf("MulVec -> a -> %.2f, b -> %.2f, c -> %.2f, d -> %.2f\n",
		(double)mul_v.x, (double)mul_v.y, (double)mul_v.z, (double)mul_v.w);
	printf("DivVec -> a -> %.2f, b -> %.2f, c -> %.2f, d -> %.2f\n",
		(double)div_v.x, (double)div_v.y, (double)div_v.z, (double)div_v.w);
}

int	main(const int argc, char **argv)
{
	t_vec4	a;
	t_vec4	b;

	if (!parse_args(argc, argv, &a, &b))
		return (1);
	process_operations(a, b);
	return (0);
}
