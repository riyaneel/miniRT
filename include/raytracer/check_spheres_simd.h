/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_spheres_simd.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 16:27:43 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 17:35:46 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_SPHERES_SIMD_H
# define CHECK_SPHERES_SIMD_H

# include "ray.h"
# include "simd_types.h"

typedef struct s_sphere_hit_ctx
{
	const t_sphere	*s;
	const t_ray		*r;
	t_vec4			*bounds;
	t_hit			*rec;
	bool			hit_any;
	uint8_t			padding[7];
}	t_sphere_hit_ctx;

static inline void	sphere_record_hit(t_sphere_hit_ctx *ctx, const int idx,
		const float t)
{
	t_vec4	center;
	t_vec4	normal;

	ctx->bounds->y = t;
	ctx->hit_any = true;
	ctx->rec->t = t;
	ctx->rec->p = ray_at(ctx->r, t);
	center.x = ctx->s->x[idx];
	center.y = ctx->s->y[idx];
	center.z = ctx->s->z[idx];
	center.w = 1.0f;
	normal = vec4_sub(ctx->rec->p, center);
	normal = vec4_scale(normal, ctx->s->inv_r[idx]);
	hit_set_face_normal(ctx->rec, ctx->r, normal);
	ctx->rec->color_obj = ctx->s->colors[idx];
	ctx->rec->type = HIT_SPHERE;
	ctx->rec->obj_center = center;
}

static inline void	sphere_process_hit(t_sphere_hit_ctx *ctx,
		const float *t_cand, const int mask_int, const int base_i)
{
	int	k;
	int	idx;

	k = 0;
	while (k < 4)
	{
		if ((mask_int >> k) & 1)
		{
			idx = base_i + k;
			if (idx >= ctx->s->count)
				break ;
			if (t_cand[k] < ctx->bounds->y)
				sphere_record_hit(ctx, idx, t_cand[k]);
		}
		k++;
	}
}

static inline int	sphere_test_roots(t_simd_hit *hit, const t_vec4 *bounds,
		float *t_cand)
{
	__m128	t_mask;
	int		mask_int;

	t_mask = _mm_and_ps(
			_mm_cmpgt_ps(hit->root1, _mm_set1_ps(bounds->x)),
			_mm_cmplt_ps(hit->root1, _mm_set1_ps(bounds->y)));
	hit->mask = _mm_and_ps(hit->mask, t_mask);
	mask_int = _mm_movemask_ps(hit->mask);
	if (mask_int != 0)
		_mm_storeu_ps(t_cand, hit->root1);
	return (mask_int);
}

#endif // CHECK_SPHERES_SIMD_H
