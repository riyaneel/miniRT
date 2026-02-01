/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tonemap.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 19:54:51 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 20:01:45 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TONEMAP_H
# define TONEMAP_H

# include <math.h>

# include "tonemap_types.h"
# include "vectors/vector_types.h"

static inline t_vec4	tonemap_reinhard(const t_vec4 c)
{
	t_vec4	result;

	result.x = c.x / (1.0f + c.x);
	result.y = c.y / (1.0f + c.y);
	result.z = c.z / (1.0f + c.z);
	result.w = c.w;
	return (result);
}

static inline float	aces_curve(const float x)
{
	float	num;
	float	den;

	num = x * (ACES_A * x + ACES_B);
	den = x * (ACES_C * x + ACES_D) + ACES_E;
	return (num / den);
}

static inline t_vec4	tonemap_aces(const t_vec4 c)
{
	t_vec4	result;

	result.x = aces_curve(c.x);
	result.y = aces_curve(c.y);
	result.z = aces_curve(c.z);
	result.w = c.w;
	return (result);
}

static inline t_vec4	gamma_correct(const t_vec4 c)
{
	t_vec4	result;

	result.x = powf(c.x, INV_GAMMA);
	result.y = powf(c.y, INV_GAMMA);
	result.z = powf(c.z, INV_GAMMA);
	result.w = c.w;
	return (result);
}

#endif // TONEMAP_H
