/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shader.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 03:44:58 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/02 16:17:14 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADER_H
# define SHADER_H

# include "bump_mapping.h"
# include "checkerboard.h"
# include "shader_light.h"
# include "soft_shadow.h"
# include "world.h"

typedef struct s_shade_ctx
{
	t_vec4			normal;
	t_vec4			point;
	t_vec4			color;
	t_vec4			view;
	t_prng_state	*rng;
	uint8_t			padding[8];
}	t_shade_ctx;

static inline t_vec4	shade_one_light(const t_scene *scn, const t_light *li,
		const t_shade_ctx *ctx)
{
	t_light_calc	lc;
	t_vec4			contrib;
	float			vis;

	vis = soft_visibility(scn, vec4_add(ctx->point,
				vec4_scale(ctx->normal, EPSILON)), li, ctx->rng);
	if (vis < EPSILON)
		return ((t_vec4){{0, 0, 0, 0}});
	lc = get_light_dir(li, ctx->point);
	contrib = compute_diffuse(li, ctx->color, ctx->normal, lc.dir);
	contrib = vec4_add(contrib,
			compute_specular(li, ctx->view, ctx->normal, lc.dir));
	return (vec4_scale(contrib, vis));
}

static inline t_vec4	shade_lights(const t_scene *scn, const t_ray *r,
		t_shade_ctx *ctx)
{
	t_vec4	result;
	int		i;

	result = (t_vec4){{0, 0, 0, 0}};
	ctx->view = vec4_scale(r->dir, -1.0f);
	i = -1;
	while (++i < scn->num_lights)
		result = vec4_add(result, shade_one_light(scn, &scn->lights[i], ctx));
	return (result);
}

static inline t_vec4	shade_ray(const t_scene *scn, const t_ray *r,
		const t_hit *rec, t_prng_state *rng)
{
	t_shade_ctx	ctx;
	t_vec4		ambient;

	ctx.color = apply_checker(rec);
	ctx.normal = apply_bump(rec);
	ctx.point = rec->p;
	ctx.rng = rng;
	ambient = vec4_mul(scn->ambient.color, ctx.color);
	return (vec4_add(ambient, shade_lights(scn, r, &ctx)));
}

#endif // SHADER_H
