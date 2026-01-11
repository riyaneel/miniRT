/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 21:21:04 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/11 21:27:15 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_UTILS_H
# define RANDOM_UTILS_H

# include <stdint.h>

typedef uint32_t	t_prng_state;

static inline uint32_t	xor_shift32(t_prng_state *state)
{
	uint32_t	x;

	x = *state;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	*state = x;
	return (x);
}

static inline float	random_float(t_prng_state *state)
{
	return ((float)xor_shift32(state) * 2.3283064365386963e-10f);
}

static inline float	random_float_range(t_prng_state *state, const float min,
		const float max)
{
	return (min + (max - min) * random_float(state));
}

static inline t_prng_state	init_rng_seed(const uint32_t x, const uint32_t y,
		const uint32_t frame)
{
	t_prng_state	seed;

	seed = (y * 1920 + x) ^ (frame * 15485863);
	seed = seed * 747796405 + 2891336453;
	seed = ((seed >> ((seed >> 28) + 4)) ^ seed) * 277803737;
	seed = (seed >> 22) ^ seed;
	return (seed);
}

#endif // RANDOM_UTILS_H
