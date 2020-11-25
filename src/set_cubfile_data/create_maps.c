/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_maps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:57:52 by monoue            #+#    #+#             */
/*   Updated: 2020/11/25 11:55:53 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "create_maps.h"

static void	exit_if_too_large_map(char *map_line, size_t height)
{
	const size_t width = ft_strlen(map_line);

	if (height > MAX_MAP_LEN - 1)
		map_exit_failure(map_line, ".cub file: The map is too high.\n");
	if (width > MAX_MAP_LEN)
		map_exit_failure(map_line, ".cub file: The map is too wide.\n");
}

static void	copy_line_to_map(const char *cubfile_line, size_t current_row)
{
	ft_strcpy(g_map[current_row], cubfile_line);
	ft_strcpy(g_map_to_check[current_row], cubfile_line);
}

static bool	is_empty_line(char *line)
{
	size_t	index;

	index = 0;
	while (line[index] == ' ')
		index++;
	return (line[index] == '\0');
}

void		create_map_array(char *map_first_line, int fd)
{
	char	*cubfile_line;
	size_t	current_height;

	copy_line_to_map(map_first_line, 0);
	current_height = 1;
	while (get_next_line(fd, &cubfile_line) > 0)
	{
		if (is_empty_line(cubfile_line))
		{
			while (get_next_line(fd, &cubfile_line) > 0)
				if (!is_empty_line(cubfile_line))
					map_exit_failure(cubfile_line, MAP_HAS_EMPTY_LINES);
		}
		else
		{
			exit_if_too_large_map(cubfile_line, current_height);
			copy_line_to_map(cubfile_line, current_height);
			SAFE_FREE(cubfile_line);
			current_height++;
		}
	}
	exit_if_too_large_map(cubfile_line, current_height);
	copy_line_to_map(cubfile_line, current_height);
}

void		init_maps(void)
{
	size_t	y_i;

	y_i = 0;
	while (y_i <= MAX_MAP_LEN)
	{
		ft_bzero(g_map[y_i], MAX_MAP_LEN + 1);
		ft_bzero(g_map_to_check[y_i], MAX_MAP_LEN + 1);
		y_i++;
	}
}
