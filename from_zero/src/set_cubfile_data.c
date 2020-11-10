/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cubfile_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:54:24 by monoue            #+#    #+#             */
/*   Updated: 2020/11/10 12:32:28 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "set_cubfile_data.h"

#include "test.h"

static char *g_ids[TEXTURES_NUM] =
{
	"NO",
	"EA",
	"WE",
	"SO",
	"S"
};

t_cubfile_data g_cubfile_data =
{
	.window_width = NOT_SET,
	.window_height = NOT_SET,
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
	if (!ft_str_is_numeric(infos[0]) || !ft_str_is_numeric(infos[1]) || ft_strlen(infos[0]) > 4 || ft_strlen(infos[1]) > 4)
		exit_with_error_message(INVALID_INFO, "R");
	// TODO: デバッグ終了後、削除
	// g_cubfile_data.window_width = 900;
	// g_cubfile_data.window_height = 900;

	// TODO: デバッグ後、コメントアウト解除
	mlx_get_screen_size(g_mlx.mlx_ptr, &g_cubfile_data.window_width, &g_cubfile_data.window_height);
	g_cubfile_data.window_width = MIN(g_cubfile_data.window_width, ft_atoi(infos[0]));
	g_cubfile_data.window_height = MIN(g_cubfile_data.window_height, ft_atoi(infos[1]));
	if (g_cubfile_data.window_width == 0 || g_cubfile_data.window_height == 0)
		exit_with_error_message(INVALID_INFO, "R");
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
// }

static void	set_texture(char **texture_path, const char **infos, char *id)
{
	if (*texture_path != NULL)
		exit_with_error_message(ID_OVERLAPPING, id);
	if (ft_count_strs(infos) != 1)
		exit_with_error_message(WRONG_INFO_NUM, id);
	*texture_path = ft_strdup(infos[0]);
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
	size_t	t_i;

	t_i = 0;
	while (t_i < TEXTURES_NUM)
	{
		if (g_textures[t_i].path == NULL)
			return (false);
		t_i++;
	}
	if (g_cubfile_data.window_width == NOT_SET || g_cubfile_data.window_height == NOT_SET)
		return (false);
	if ((int)g_cubfile_data.floor_color == NOT_SET || (int)g_cubfile_data.ceiling_color == NOT_SET)
		return (false);
	return (true);
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
	size_t	sprites_count;

	sprites_count = 0;
	y = 0;
	while (g_map[y][0] != '\0')
	{
		x = 0;
		while ((current_c = g_map[y][x]) != '\0')
		{
			if (current_c == '2')
			{
				set_sprite_data(x, y, sprites_count);
				sprites_count++;
			}
			else if (is_spawn_point_c(current_c))
			{
				if (map_has_double_spawn_points())
					exit_with_error_message(SINGLE, "The map has several spawn points.\n");
				set_player_spawning_data(x, y, current_c);
			}
			x++;
		}
		y++;
	}
	g_cubfile_data.sprites_num = sprites_count;
}

// TODO: textures の path、初期化する
void	exit_if_not_all_elements_are_set(void)
{
	size_t	t_i;

	t_i = 0;
	while (t_i < TEXTURES_NUM)
	{
		if (g_textures[t_i].path == NULL)
			exit_with_error_message(LACKING_ELEMENT, g_ids[t_i]);
		t_i++;
	}
	if (g_cubfile_data.window_width == NOT_SET)
		exit_with_error_message(LACKING_ELEMENT, "R");
	if ((int)g_cubfile_data.floor_color == NOT_SET)
		exit_with_error_message(LACKING_ELEMENT, "F");
	if ((int)g_cubfile_data.ceiling_color == NOT_SET)
		exit_with_error_message(LACKING_ELEMENT, "C");
}

static void	get_line_data(char *cubfile_line, int fd)
{
	const char	**element_items = (const char **)ft_split(cubfile_line, ' ');
	size_t		t_i;

	if (element_items[0] == NULL)
		return ;
	if (!all_elements_are_set() && is_map_line(cubfile_line))
	// {
		// DI(all_elements_are_set());
		// DS(cubfile_line);
		// test_all_cubfile_data();
		exit_with_error_message(SINGLE, "The map is in the wrong place.");
	// }
	t_i = 0;
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
		while (t_i < TEXTURES_NUM)
		{
			if (ft_strcmp(element_items[0], g_ids[t_i]) == 0)
			{
				// set_texture(&g_textures[t_i].path, &element_items[1], g_ids[t_i]);
				set_texture(&g_textures[t_i].path, &element_items[1], g_ids[t_i]);
				break ;
			}
			t_i++;
		}
}

void	set_cubfile_data(char *filename)
{
	char		*line;
	const int	fd = open(filename, O_RDONLY);

	// map_init(data);
	// data->err_flag = false;
	if (fd == ERROR)
		exit_with_error_message(SINGLE, ".cub file cloud not be opened.\n");
	init_maps();
	init_texture_paths();
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
	exit_if_map_is_not_surrounded_by_walls(g_player.grid_x, g_player.grid_y);

	// TODO: sprite の malloc の必然性が分からない
	// なので後回し
	// data->sprite = malloc(sizeof(t_sprite) * data->sprite_num);
	// TODO: 同じく、sprite の位置の獲得の必然性もわからないので後で
	// get_sprites_positions(data);
	// check(data);
}