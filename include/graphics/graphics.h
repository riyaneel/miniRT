/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 19:46:18 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/11 20:40:54 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include <stdbool.h>

# include "graphics_types.h"
# include "allocator/arena_allocator_types.h"

bool	graphics_init(t_graphics *gfx, t_arena *arena, int w, int h);

void	graphics_shutdown(t_graphics *gfx);

void	graphics_present(const t_graphics *gfx);

void	graphics_clear(t_graphics *gfx);

void	graphics_setup_hooks(t_graphics *gfx);

#endif // GRAPHICS_H
