/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_config.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:54:24 by monoue            #+#    #+#             */
/*   Updated: 2020/11/30 14:53:54 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "set_config.h"

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
				set_sprite_position(x, y, g_config.sprites_num);
				g_config.sprites_num++;
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

static void	set_texture_if_valid(const char **element_items)
{
	size_t		t_i;

	t_i = 0;
	while (t_i < TEXTURES_NUM)
	{
		if (ft_strcmp(element_items[0], g_ids[t_i]) == 0)
		{
			set_texture(&g_textures[t_i].path, &element_items[1],
																g_ids[t_i]);
			break ;
		}
		t_i++;
	}
}

static void	get_line_data(char *config_line, int fd)
{
	const char	**element_items = (const char **)ft_split(config_line, ' ');

	if (element_items[0] == NULL)
		return ;
	if (!all_elements_are_set() && is_map_line(config_line))
		exit_closing_fd(SINGLE, MAP_WRONG_PLACE, fd);
	if (ft_strcmp(element_items[0], "R") == 0)
		get_resolution(&element_items[1], fd);
	else if (ft_strcmp(element_items[0], "F") == 0)
		set_color(&g_config.floor_color, &element_items[1], "F");
	else if (ft_strcmp(element_items[0], "C") == 0)
		set_color(&g_config.ceiling_color, &element_items[1], "C");
	else if (is_map_line(config_line))
	{
		exit_if_not_all_elements_are_set(fd);
		create_map_array(config_line, fd);
	}
	else
		set_texture_if_valid(element_items);
}

void		set_config(char *filename)
{
	char		*line;
	const int	fd = open(filename, O_RDONLY);

	if (fd == ERROR)
		exit_with_error_message(ERRNO, NULL);
	init_maps();
	init_texture_paths();
	while (get_next_line(fd, &line) > 0)
	{
		get_line_data(line, fd);
		if (g_map[0][0] != '\0')
			break ;
		SAFE_FREE(line);
	}
	exit_if_closing_fd_fails(fd);
	g_config.sprites_num = 0;
	set_spawn_data_and_sprites_num();
	if (g_map[0][0] == '\0')
		exit_with_error_message(SINGLE, NO_MAP);
	if (g_player.x == NOT_SET || g_player.y == NOT_SET)
		exit_with_error_message(SINGLE, PLAYER_NOT_IN_MAP);
	exit_if_map_is_not_surrounded_by_walls(g_player.grid_x, g_player.grid_y);
}
