/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_present.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/11 20:04:49 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/16 12:02:40 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <immintrin.h>

#include "graphics/graphics.h"
#include "utils/maths_utils.h"

static inline int	vec4_to_bgra(const t_vec4 color)
{
	const float			r = fclamp(color.x, 0.0f, 1.0f);
	const float			g = fclamp(color.y, 0.0f, 1.0f);
	const float			b = fclamp(color.z, 0.0f, 1.0f);
	const unsigned int	ir = (unsigned)(r * 255.99f);
	const unsigned int	ig = (unsigned)(g * 255.99f);

	return ((int)(0xFF000000 | (ir << 16)
		| (ig << 8) | (unsigned)(b * 255.99f)));
}

static inline void	process_block_sse(const t_vec4 *src, int *dst, int i)
{
	__m128	v[4];
	__m128i	vi[2];
	__m128i	res;

	v[0] = _mm_load_ps((const float *)&src[i]);
	v[1] = _mm_load_ps((const float *)&src[i + 1]);
	v[2] = _mm_load_ps((const float *)&src[i + 2]);
	v[3] = _mm_load_ps((const float *)&src[i + 3]);
	v[0] = _mm_shuffle_ps(v[0], v[0], 0xC6);
	v[1] = _mm_shuffle_ps(v[1], v[1], 0xC6);
	v[2] = _mm_shuffle_ps(v[2], v[2], 0xC6);
	v[3] = _mm_shuffle_ps(v[3], v[3], 0xC6);
	v[0] = _mm_mul_ps(v[0], _mm_set1_ps(255.99f));
	v[1] = _mm_mul_ps(v[1], _mm_set1_ps(255.99f));
	v[2] = _mm_mul_ps(v[2], _mm_set1_ps(255.99f));
	v[3] = _mm_mul_ps(v[3], _mm_set1_ps(255.99f));
	vi[0] = _mm_packs_epi32(_mm_cvttps_epi32(v[0]), _mm_cvttps_epi32(v[1]));
	vi[1] = _mm_packs_epi32(_mm_cvttps_epi32(v[2]), _mm_cvttps_epi32(v[3]));
	res = _mm_packus_epi16(vi[0], vi[1]);
	_mm_storeu_si128((void *)&dst[i],
		_mm_or_si128(res, _mm_set1_epi32((int)0xFF000000)));
}

void	graphics_present(const t_graphics *gfx)
{
	const int	count = gfx->width * gfx->height;
	t_vec4		*src;
	int			*dst;
	int			i;

	src = gfx->framebuffer->pixels;
	dst = gfx->win->pixel_buffer;
	i = 0;
	while (i <= count - 4)
	{
		process_block_sse(src, dst, i);
		i += 4;
	}
	while (i < count)
	{
		dst[i] = vec4_to_bgra(src[i]);
		i++;
	}
}
