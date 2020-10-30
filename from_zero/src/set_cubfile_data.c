/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cubfile_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:54:24 by monoue            #+#    #+#             */
/*   Updated: 2020/10/30 13:03:27 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "set_cubfile_data.h"
#include "init_mlx.h"

t_cubfile_data g_cubfile_data =
{
	.window_width = NOT_SET,
	.window_height = NOT_SET,
	.north_texture_path = NULL,
	.south_texture_path = NULL,
	.west_texture_path = NULL,
	.east_texture_path = NULL,
	.sprite_texture_path = NULL,
	.floor_color = NOT_SET,
	.ceiling_color = NOT_SET,

};


/*
** If a render size is of more than four digits, it is taken to be invalid size.
*/
void	get_resolution(const char **infos)
{
	if (!(g_cubfile_data.window_width == NOT_SET && g_cubfile_data.window_height == NOT_SET))
		exit_with_error_message(ID_OVERLAPPING, "R");
	if (ft_count_strs(infos) != 2)
		exit_with_error_message(WRONG_INFO_NUM, "R");
	if (!ft_str_is_numeric(infos[0]) || !ft_str_is_numeric(infos[1]) || ft_strlen(infos[0]) > 4 || ft_strlen(infos[0]) > 4)
		exit_with_error_message(INVALID_INFO, "R");
	// TODO: デバッグ終了後、削除
	g_cubfile_data.window_width = 500;
	g_cubfile_data.window_height = 500;

	// TODO: デバッグ後、コメントアウト解除
	// mlx_get_screen_size(g_data.mlx, &g_cubfile_data.window_width, &g_cubfile_data.window_height);
	// g_cubfile_data.window_width = MIN(g_cubfile_data.window_width, ft_atoi(infos[0]));
	// g_cubfile_data.window_height = MIN(g_cubfile_data.window_height, ft_atoi(infos[1]));
	// if (g_cubfile_data.window_width == 0 || g_cubfile_data.window_height == 0)
	// 	exit_with_error_message(INVALID_INFO, "R");
	// printf("%d, %d\n", g_cubfile_data.window_width, g_cubfile_data.window_height);

}

// 一応残しておく
// void	set_texture(char **texture_path, const char **infos, char *id)
// {
// 	size_t	texture_i;

// 	if (*texture_path != NULL)
// 		exit_with_error_message(ID_OVERLAPPING, id);
// 	if (ft_count_strs(infos) != 1)
// 		exit_with_error_message(WRONG_INFO_NUM, id);
// 	texture_i = 0;
// 	// printf("%s\n", g_texture_file_names[GREYSTONE]);
// 	// printf("%s\n", infos[0]);
// 	while (texture_i < TEXTURES_NUM)
// 	{
// 		if (ft_strcmp(id, "NO") == 0)
// 			g_cubfile_data.north_texture_path = ft_strdup(infos[0]);
// 		else if (ft_strcmp(id, "EA") == 0)
// 			g_cubfile_data.east_texture_path = ft_strdup(infos[0]);
// 		else if (ft_strcmp(id, "WE") == 0)
// 			g_cubfile_data.west_texture_path = ft_strdup(infos[0]);
// 		else if (ft_strcmp(id, "SO") == 0)
// 			g_cubfile_data.south_texture_path = ft_strdup(infos[0]);
// 		else if (ft_strcmp(id, "S") == 0)
// 			g_cubfile_data.sprite_texture_path = ft_strdup(infos[0]);
// 		break ;
// 		texture_i++;
// 	}
// 	if (texture_i == TEXTURES_NUM)
// 		exit_with_error_message(INVALID_PATH, id);
// 	// printf("%s\n", g_cubfile_data.north_texture_path);
// }

static void	set_texture(char *texture_path, const char **infos, char *id)
{
	if (texture_path != NULL)
		exit_with_error_message(ID_OVERLAPPING, id);
	if (ft_count_strs(infos) != 1)
		exit_with_error_message(WRONG_INFO_NUM, id);
	texture_path = ft_strdup(infos[0]);
}


bool	is_spawn_point_c(char c)
{
	return (c == 'N' || c == 'E' || c == 'W' || c == 'S');
}

static bool	is_map_c(char c)
{
	return ((c >= '0' && c <= '2') || is_spawn_point_c(c) || c == ' ');
}

bool	is_map_line(const char *cubfile_line)
{
	size_t	index;

	index = 0;
	while (cubfile_line[index] == ' ')
		index++;
	if (cubfile_line[index] == '\0')
		return (false);
	while (is_map_c(cubfile_line[index]))
		index++;
	return (cubfile_line[index] == '\0');
}

bool	all_elements_are_set(void)
{
	return (!(g_cubfile_data.window_width == NOT_SET
	|| g_cubfile_data.window_height == NOT_SET
	|| g_cubfile_data.north_texture_path == NULL
	|| g_cubfile_data.east_texture_path == NULL
	|| g_cubfile_data.west_texture_path == NULL
	|| g_cubfile_data.south_texture_path == NULL
	|| g_cubfile_data.sprite_texture_path == NULL
	|| (int)g_cubfile_data.floor_color == NOT_SET
	|| (int)g_cubfile_data.ceiling_color == NOT_SET));
}

bool	map_has_double_spawn_points()
{
	if ((int)g_player.x != NOT_SET)
		return (true);
	return (false);
}

void	set_spawn_data_and_sprites_num(void)
{
	size_t	y;
	size_t	x;
	char	current_c;

	g_cubfile_data.sprites_num = 0;
	y = 0;
	while (g_map[y][0] != '\0')
	{
		x = 0;
		while ((current_c = g_map[y][x]) != '\0')
		{
			if (current_c == '2')
				g_cubfile_data.sprites_num++;
			if (is_spawn_point_c(current_c))
			{
				if (map_has_double_spawn_points())
					exit_with_error_message(SINGLE, "The map has several spawn points.\n");
				set_player_spawning_data(x, y, current_c);
			}
			x++;
		}
		y++;
	}
}

void	exit_if_not_all_elements_are_set(void)
{
	if (g_cubfile_data.window_width == NOT_SET)
		exit_with_error_message(LACKING_ELEMENT, "R");
	if (g_cubfile_data.north_texture_path == NULL)
		exit_with_error_message(LACKING_ELEMENT, "NO");
	if (g_cubfile_data.east_texture_path == NULL)
		exit_with_error_message(LACKING_ELEMENT, "EA");
	if (g_cubfile_data.west_texture_path == NULL)
		exit_with_error_message(LACKING_ELEMENT, "WE");
	if (g_cubfile_data.south_texture_path == NULL)
		exit_with_error_message(LACKING_ELEMENT, "SO");
	if (g_cubfile_data.sprite_texture_path == NULL)
		exit_with_error_message(LACKING_ELEMENT, "S");
	if ((int)g_cubfile_data.floor_color == NOT_SET)
		exit_with_error_message(LACKING_ELEMENT, "F");
	if ((int)g_cubfile_data.ceiling_color == NOT_SET)
		exit_with_error_message(LACKING_ELEMENT, "C");
}

static void	get_line_data(char *cubfile_line, int fd)
{
	const char **element_items = (const char **)ft_split(cubfile_line, ' ');

	if (element_items[0] == NULL)
		return ;
	if (!all_elements_are_set() && is_map_line(cubfile_line))
		exit_with_error_message(SINGLE, "The map is in the wrong place.");
	if (ft_strcmp(element_items[0], "R") == 0)
		get_resolution(&element_items[1]);
	else if (ft_strcmp(element_items[0], "NO") == 0)
		set_texture(g_textures[WALL_N].path, &element_items[1], "NO");
	else if (ft_strcmp(element_items[0], "EA") == 0)
		set_texture(g_textures[WALL_E].path, &element_items[1], "EA");
	else if (ft_strcmp(element_items[0], "WE") == 0)
		set_texture(g_textures[WALL_W].path, &element_items[1], "WE");
	else if (ft_strcmp(element_items[0], "SO") == 0)
		set_texture(g_textures[WALL_S].path, &element_items[1], "SO");
	else if (ft_strcmp(element_items[0], "S") == 0)
		set_texture(g_textures[SPRITE].path, &element_items[1], "S");
	else if (ft_strcmp(element_items[0], "F") == 0)
		set_color(&g_cubfile_data.floor_color, &element_items[1], "F");
	else if (ft_strcmp(element_items[0], "C") == 0)
		set_color(&g_cubfile_data.ceiling_color, &element_items[1], "C");
	else if (is_map_line(cubfile_line))
	{
		exit_if_not_all_elements_are_set();
		create_map_array(cubfile_line, fd);
	}
	// printf("%s\n", g_cubfile_data.north_texture_path);
	// printf("%s\n", g_cubfile_data.east_texture_path);
	// printf("%s\n", g_cubfile_data.west_texture_path);
	// printf("%s\n", g_cubfile_data.south_texture_path);
	// printf("%s\n", g_cubfile_data.sprite_texture_path);
	// printf("%d\n", g_cubfile_data.window_width);
	// printf("%d\n", g_cubfile_data.window_height);
	// printf("%d\n", g_cubfile_data.floor_color);
	// printf("%d\n", g_cubfile_data.ceiling_color);
}

void	set_cubfile_data(char *filename)
{
	char		*line;
	const int	fd = open(filename, O_RDONLY);

	// map_init(data);
	// data->err_flag = false;
	if (fd == ERROR)
		exit_with_error_message(SINGLE, ".cub file cloud not be opened.\n");
	initialize_map();
	while (get_next_line(fd, &line) > 0)
	{
		// printf("%s\n", line);
		get_line_data(line, fd);
		if (g_map[0][0] != '\0')
			break ;
		SAFE_FREE(line);
	}
	// マップ出力テスト
	// size_t	index = 0;
	// while(index < 50)
	// {
	// 	printf("%s\n", g_map[index]);
	// 	index++;
	// }
	set_spawn_data_and_sprites_num();
	exit_if_map_is_not_surrounded_by_walls(g_player.x, g_player.y);

	// TODO: sprite の malloc の必然性が分からない
	// なので後回し
	// data->sprite = malloc(sizeof(t_sprite) * data->sprite_num);
	// TODO: 同じく、sprite の位置の獲得の必然性もわからないので後で
	// get_sprites_positions(data);
	// check(data);
}