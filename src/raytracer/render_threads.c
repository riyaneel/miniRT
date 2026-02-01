/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 16:05:22 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/02/01 16:07:07 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>

#include "raytracer/render.h"

void	free_thread_data(t_thread_data *data, const int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (data[i].buffer)
			free(data[i].buffer);
		i++;
	}
	free(data);
}

void	spawn_threads(pthread_t *th, t_thread_data *data, const int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (pthread_create(&th[i], NULL, thread_routine, &data[i]) != 0)
			break ;
		i++;
	}
}

void	join_threads(const pthread_t *th, t_thread_data *data, const int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_join(th[i], NULL);
		i++;
	}
	free_thread_data(data, n);
}

void	*thread_routine(void *arg)
{
	t_thread_data	*data;
	int				tile_idx;

	data = (t_thread_data *)arg;
	while (1)
	{
		tile_idx = __atomic_fetch_add(&data->ctx->next_tile, 1,
				__ATOMIC_RELAXED);
		if (tile_idx >= data->ctx->total_tiles)
			break ;
		render_tile(data->ctx, tile_idx, data->buffer);
	}
	return (NULL);
}
