/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_formatting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 22:16:56 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/11 23:10:10 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene/scene_parser.h"

#include "core/ctype/ft_ctype.h"

void	skip_formatting(char **p)
{
	while (**p && ft_isspace(**p) && **p != '\n')
		(*p)++;
}
