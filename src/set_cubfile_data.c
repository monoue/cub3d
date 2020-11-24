/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cubfile_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:54:24 by monoue            #+#    #+#             */
/*   Updated: 2020/11/24 13:37:53 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "set_cubfile_data.h"
#include "test.h"

static bool	map_has_double_spawn_points(void)
{
	if ((int)g_player.x != NOT_SET)
		return (true);
	return (false);
}

static void	set_spawn_data_and_sprites_num(void)
{
	size_t	y;
	size_t	x;
	char	current_c;

	y = 0;
	while (g_map[y][0] != '\0')
	{
		x = 0;
		while ((current_c = g_map[y][x]) != '\0')
		{
			if (current_c == SPRITE_C)
			{
				set_sprite_basic_data(x, y, g_cubfile_data.sprites_num);
				g_cubfile_data.sprites_num++;
			}
			else if (is_spawn_point_c(current_c))
			{
				if (map_has_double_spawn_points())
					exit_with_error_message(SINGLE, SEVERAL_SPAWN_POINTS);
				set_player_spawning_data(x, y, current_c);
			}
			x++;
		}
		y++;
	}
}

static void	init_texture_paths(void)
{
	size_t	t_i;

	t_i = 0;
	while (t_i < TEXTURES_NUM)
	{
		g_textures[t_i].path = NULL;
		t_i++;
	}
}

static void	get_line_data(char *cubfile_line, int fd)
{
	const char	**element_items = (const char **)ft_split(cubfile_line, ' ');

	if (element_items[0] == NULL)
		return ;
	if (!all_elements_are_set() && is_map_line(cubfile_line))
		exit_with_error_message(SINGLE, MAP_WRONG_PLACE);
	if (ft_strcmp(element_items[0], "R") == 0)
		get_resolution(&element_items[1]);
	else if (ft_strcmp(element_items[0], "F") == 0)
		set_color(&g_cubfile_data.floor_color, &element_items[1], "F");
	else if (ft_strcmp(element_items[0], "C") == 0)
		set_color(&g_cubfile_data.ceiling_color, &element_items[1], "C");
	else if (is_map_line(cubfile_line))
	{
		exit_if_not_all_elements_are_set();
		create_map_array(cubfile_line, fd);
	}
	else
		set_texture_if_valid(element_items);
}

void		set_cubfile_data(char *filename)
{
	char		*line;
	const int	fd = open(filename, O_RDONLY);

	if (fd == ERROR)
		exit_with_error_message(SINGLE, ".cub file cloud not be opened.\n");
	init_maps();
	init_texture_paths();
	while (get_next_line(fd, &line) > 0)
	{
		get_line_data(line, fd);
		if (g_map[0][0] != '\0')
			break ;
		SAFE_FREE(line);
	}
	g_cubfile_data.sprites_num = 0;
	set_spawn_data_and_sprites_num();
	exit_if_map_is_not_surrounded_by_walls(g_player.grid_x, g_player.grid_y);
}
