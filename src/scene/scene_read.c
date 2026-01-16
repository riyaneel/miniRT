/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-qoqu <rel-qoqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 08:17:05 by rel-qoqu          #+#    #+#             */
/*   Updated: 2026/01/16 08:21:57 by rel-qoqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

#include "scene/scene_parser.h"

static int	get_file_size(const int fd)
{
	int	len;

	len = (int)lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	return (len);
}

static inline char	*close_exit(const int fd)
{
	close(fd);
	return (NULL);
}

char	*read_file_to_arena(t_arena *arena, const char *file)
{
	int		fd;
	int		len;
	char	*buf;
	ssize_t	bytes;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	len = get_file_size(fd);
	if (len <= 0)
		return (close_exit(fd));
	buf = arena_alloc(arena, (size_t)len + 1);
	if (!buf)
		return (close_exit(fd));
	bytes = read(fd, buf, (size_t)len);
	close(fd);
	if (bytes < 0)
		return (NULL);
	buf[bytes] = '\0';
	return (buf);
}
