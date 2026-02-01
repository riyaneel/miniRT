/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_process.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 19:56:02 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 20:01:50 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POST_PROCESS_H
# define POST_PROCESS_H

# include "tonemap.h"
# include "utils/maths_utils.h"

static inline t_vec4	clamp_color(const t_vec4 c)
{
	t_vec4	result;

	result.x = fmin_fast(fmax_fast(c.x, 0.0f), 1.0f);
	result.y = fmin_fast(fmax_fast(c.y, 0.0f), 1.0f);
	result.z = fmin_fast(fmax_fast(c.z, 0.0f), 1.0f);
	result.w = c.w;
	return (result);
}

static inline t_vec4	post_process(const t_vec4 hdr_color)
{
	t_vec4	mapped;
	t_vec4	corrected;

	mapped = tonemap_aces(hdr_color);
	corrected = gamma_correct(mapped);
	return (clamp_color(corrected));
}

static inline t_vec4	post_process_reinhard(const t_vec4 hdr_color)
{
	t_vec4	mapped;
	t_vec4	corrected;

	mapped = tonemap_reinhard(hdr_color);
	corrected = gamma_correct(mapped);
	return (clamp_color(corrected));
}

#endif // POST_PROCESS_H
