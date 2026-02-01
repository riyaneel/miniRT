/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 12:44:41 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 13:01:12 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/scene_validate.h"

#include "io/ft_printf.h"

bool	validate_ratio(const float ratio, const char *name)
{
	if (ratio < 0.0f || ratio > 1.0f)
	{
		ft_dprintf(2, "Error\n%s: ratio must be in range [0.0, 1.0]\n", name);
		return (false);
	}
	return (true);
}

bool	validate_fov(const float fov)
{
	if (fov < 0.0f || fov > 180.0f)
	{
		ft_dprintf(2, "Error\nCamera: FOV must be in range [0.0, 180]\n");
		return (false);
	}
	return (true);
}

bool	validate_normalized_vec(const t_vec4 vec, const char *name)
{
	if (vec.x < -1.0f || vec.x > 1.0f || vec.y < -1.0f || vec.y > 1.0f
		|| vec.z < -1.0f || vec.z > 1.0f)
	{
		ft_dprintf(2,
			"Error\n%s: vector components must be in range [-1, 1]\n", name);
		return (false);
	}
	return (true);
}

bool	validate_color_range(const t_vec4 color, const char *name)
{
	if (color.x < 0.0f || color.x > 255.0f || color.y < 0.0f
		|| color.y > 255.0f || color.z < 0.0f || color.z > 255.0f)
	{
		ft_dprintf(2,
			"Error\n%s: color values must be in range [0, 255]\n", name);
		return (false);
	}
	return (true);
}
