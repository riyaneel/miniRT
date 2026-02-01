/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_mapping.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 19:24:37 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 19:37:39 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUMP_MAPPING_H
# define BUMP_MAPPING_H

# include <math.h>

# include "bump_types.h"
# include "ray_types.h"
# include "vectors/rt_vectors.h"

static inline float	bump_height(const t_vec4 p)
{
	float	h1;
	float	h2;

	h1 = sinf(p.x * BUMP_FREQ_1) * sinf(p.y * BUMP_FREQ_1)
		* sinf(p.z * BUMP_FREQ_1);
	h2 = sinf(p.x * BUMP_FREQ_2) * sinf(p.y * BUMP_FREQ_2)
		* sinf(p.z * BUMP_FREQ_2);
	return (h1 + 0.5f * h2);
}

static inline t_vec4	bump_gradient(const t_vec4 p)
{
	t_vec4	grad;
	float	inv_2eps;

	inv_2eps = 1.0f / (2.0f * BUMP_EPS);
	grad.x = (bump_height((t_vec4){{p.x + BUMP_EPS, p.y, p.z, 0}})
			- bump_height((t_vec4){{p.x - BUMP_EPS, p.y, p.z, 0}})) * inv_2eps;
	grad.y = (bump_height((t_vec4){{p.x, p.y + BUMP_EPS, p.z, 0}})
			- bump_height((t_vec4){{p.x, p.y - BUMP_EPS, p.z, 0}})) * inv_2eps;
	grad.z = (bump_height((t_vec4){{p.x, p.y, p.z + BUMP_EPS, 0}})
			- bump_height((t_vec4){{p.x, p.y, p.z - BUMP_EPS, 0}})) * inv_2eps;
	grad.w = 0.0f;
	return (grad);
}

static inline t_vec4	apply_bump(const t_hit *rec)
{
	t_vec4	grad;
	t_vec4	perturb;

	if (rec->type == HIT_PLANE || rec->type == HIT_NONE
		|| rec->type == HIT_MESH)
		return (rec->normal);
	grad = bump_gradient(rec->p);
	perturb = vec4_sub(rec->normal, vec4_scale(grad, BUMP_STRENGTH));
	return (vec4_normalize(perturb));
}

#endif // BUMP_MAPPING_H
