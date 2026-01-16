/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 10:10:44 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/16 10:51:44 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_UTILS_H
# define VECTOR_UTILS_H

# include "vector_types.h"

static inline t_vec4	vec4_min(const t_vec4 a, const t_vec4 b)
{
	return ((t_vec4){.v = __builtin_ia32_minps(a.v, b.v)});
}

static inline t_vec4	vec4_max(const t_vec4 a, const t_vec4 b)
{
	return ((t_vec4){.v = __builtin_ia32_maxps(a.v, b.v)});
}

#endif // VECTOR_UTILS_H
