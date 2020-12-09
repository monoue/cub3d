/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 16:02:36 by monoue            #+#    #+#             */
/*   Updated: 2020/12/09 16:03:55 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_exit.h"

void	exit_if_too_large_map(char *map_line, size_t height, int fd)
{
	const size_t width = ft_strlen(map_line);

	if (height > MAX_MAP_LEN)
		map_exit_failure(map_line, MAP_TOO_HIGH, fd);
	if (width > MAX_MAP_LEN)
		map_exit_failure(map_line, MAP_TOO_WIDE, fd);
}

void	map_exit_failure(char *map_line, char *error_message, int fd)
{
	SAFE_FREE(map_line);
	exit_if_closing_fd_error(fd);
	exit_with_error_message(SINGLE, error_message);
}
