/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_maps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:57:52 by monoue            #+#    #+#             */
/*   Updated: 2020/12/09 09:50:37 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "create_maps.h"

static void	exit_if_too_large_map(char *map_line, size_t height, int fd)
{
	const size_t width = ft_strlen(map_line);

	if (height > MAX_MAP_LEN)
		map_exit_failure(map_line, MAP_TOO_HIGH, fd);
	if (width > MAX_MAP_LEN)
		map_exit_failure(map_line, MAP_TOO_WIDE, fd);
}

static void	copy_line_to_map(const char *config_line, size_t current_row)
{
	ft_strcpy(g_map[current_row], config_line);
	ft_strcpy(g_map_to_check[current_row], config_line);
}

static bool	is_empty_line(char *line)
{
	size_t	index;

	index = 0;
	while (line[index] == ' ')
		index++;
	return (line[index] == '\0');
}

/*
** reads config file's map and sets it to g_map and g_map_grid.
*/

void		create_map_array(char *map_first_line, int fd)
{
	char	*config_line;
	size_t	current_height;
	int		gnl_ret;

	copy_line_to_map(map_first_line, 0);
	SAFE_FREE(map_first_line);
	current_height = 1;
	while ((gnl_ret = get_next_line(fd, &config_line)) >= 0)
	{
		if (is_empty_line(config_line))
		{
			while (get_next_line(fd, &config_line) > 0)
				if (!is_empty_line(config_line))
					map_exit_failure(config_line, MAP_HAS_EMPTY_LINES, fd);
		}
		else
		{
			exit_if_too_large_map(config_line, current_height, fd);
			copy_line_to_map(config_line, current_height);
			SAFE_FREE(config_line);
			if (gnl_ret == FILE_END)
				return ;
			current_height++;
		}
	}
}

/*
** initializes g_map and g_map_grid before setting map data.
*/

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
