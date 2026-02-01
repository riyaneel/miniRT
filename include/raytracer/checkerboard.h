/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 17:11:24 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 17:35:23 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKERBOARD_H
# define CHECKERBOARD_H

# include "checkerboard_objects.h"

static inline t_vec4	apply_checker(const t_hit *rec)
{
	if (rec->type == HIT_PLANE)
		return (checker_plane(rec));
	if (rec->type == HIT_SPHERE)
		return (checker_sphere(rec));
	if (rec->type == HIT_CYLINDER)
		return (checker_cylinder(rec));
	return (rec->color_obj);
}

#endif // CHECKERBOARD_H
