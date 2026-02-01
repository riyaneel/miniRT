/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_validate.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 12:42:34 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 13:01:05 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_VALIDATE_H
# define SCENE_VALIDATE_H

# include <stdbool.h>

# include "vectors/vector_types.h"

bool	validate_ratio(float ratio, const char *name);
bool	validate_fov(float fov);
bool	validate_normalized_vec(t_vec4 vec, const char *name);
bool	validate_color_range(t_vec4 color, const char *name);

#endif // SCENE_VALIDATE_H
