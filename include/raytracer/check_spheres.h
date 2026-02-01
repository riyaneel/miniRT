/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_spheres.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 16:28:09 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 16:31:05 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_SPHERES_H
# define CHECK_SPHERES_H

# include "check_spheres_simd.h"

static inline void	sphere_check_disc(t_sphere_hit_ctx *ctx, t_simd_hit *hit,
		const t_simd_oc *oc, const int i)
{
	float	t_cand[4];
	int		mask_int;

	if (_mm_movemask_ps(hit->mask) == 0)
		return ;
	hit->sqrt_disc = _mm_sqrt_ps(hit->disc);
	hit->root1 = _mm_sub_ps(
			_mm_mul_ps(oc->dot_dir, _mm_set1_ps(-1.0f)), hit->sqrt_disc);
	mask_int = sphere_test_roots(hit, ctx->bounds, t_cand);
	if (mask_int != 0)
		sphere_process_hit(ctx, t_cand, mask_int, i);
}

static inline void	sphere_iter(t_sphere_hit_ctx *ctx, const t_simd_ray *sr,
		const int i)
{
	t_simd_sphere	ss;
	t_simd_oc		oc;
	t_simd_hit		hit;

	simd_sphere_load(&ss, ctx->s, i);
	simd_compute_oc(&oc, sr, &ss);
	simd_compute_disc(&hit, &oc, &ss);
	sphere_check_disc(ctx, &hit, &oc, i);
}

static inline bool	check_spheres_loop(t_sphere_hit_ctx *ctx,
		const t_simd_ray *sr)
{
	int	i;

	i = 0;
	while (i < ctx->s->count)
	{
		sphere_iter(ctx, sr, i);
		i += 4;
	}
	return (ctx->hit_any);
}

static inline bool	check_spheres(const t_scene *scn, const t_ray *r,
		t_vec4 *bounds, t_hit *rec)
{
	t_sphere_hit_ctx	ctx;
	t_simd_ray			sr;

	ctx.s = &scn->spheres;
	ctx.r = r;
	ctx.bounds = bounds;
	ctx.rec = rec;
	ctx.hit_any = false;
	simd_ray_init(&sr, r);
	return (check_spheres_loop(&ctx, &sr));
}

#endif // CHECK_SPHERES_H
