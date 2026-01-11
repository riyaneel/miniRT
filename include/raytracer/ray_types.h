/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:27:39 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/11 21:38:16 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_TYPES_H
# define RAY_TYPES_H

# include <stdbool.h>

# include "vectors/vector_types.h"

typedef struct s_ray {
	t_vec4	origin;
	t_vec4	dir;
}	t_ray;

typedef struct s_hit_record {
	t_vec4	p;
	t_vec4	normal;
	float	t;
	bool	front_face;
	char	padding[11];
}	t_hit;

#endif // RAY_TYPES_H
