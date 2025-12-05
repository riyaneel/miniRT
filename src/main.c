/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 13:42:42 by rel-qoqu          #+#    #+#             */
/*   Updated: 2025/12/05 14:37:48 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "rt_vectors.h"

int	main(void)
{
	const t_vec4	a = {(float)1.0, (float)2.0, (float)3.0, (float)4.0};
	const t_vec4	b = {(float)1.5, (float)2.5, (float)3.5, (float)4.5};
	const t_vec4	final = vec4_add(a, b);

	printf("a -> %.2f, b -> %.2f, c -> %.2f, d -> %.2f\n",
		(double)final.x, (double)final.y, (double)final.z, (double)final.w);
	return (0);
}
