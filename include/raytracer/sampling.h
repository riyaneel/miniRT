/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sampling.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 15:10:15 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/02 16:15:45 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAMPLING_H
# define SAMPLING_H

# include <math.h>

# include "utils/random_utils.h"
# include "vectors/rt_vectors.h"

static inline t_vec4	random_in_disk(t_prng_state *rng)
{
	t_vec4	p;

	p.x = random_float_range(rng, -1.0f, 1.0f);
	p.y = random_float_range(rng, -1.0f, 1.0f);
	p.z = 0.0f;
	p.w = 0.0f;
	while (p.x * p.x + p.y * p.y >= 1.0f)
	{
		p.x = random_float_range(rng, -1.0f, 1.0f);
		p.y = random_float_range(rng, -1.0f, 1.0f);
	}
	return (p);
}

static inline void	build_basis(const t_vec4 n, t_vec4 *u, t_vec4 *v)
{
	t_vec4	a;

	if (fabsf(n.x) > 0.9f)
		a = (t_vec4){{0, 1, 0, 0}};
	else
		a = (t_vec4){{1, 0, 0, 0}};
	*u = vec4_normalize(vec4_cross(n, a));
	*v = vec4_cross(n, *u);
}

static inline t_vec4	sample_disk_3d(const t_vec4 center, const t_vec4 dir,
		const float radius, t_prng_state *rng)
{
	t_vec4	disk;
	t_vec4	u;
	t_vec4	v;

	disk = random_in_disk(rng);
	build_basis(dir, &u, &v);
	return (vec4_add(center,
			vec4_add(vec4_scale(u, disk.x * radius),
				vec4_scale(v, disk.y * radius))));
}

#endif // SAMPLING_H
