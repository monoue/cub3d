#include "new.h"

int		exit_failure_with_error_message(char *msg)
{
	ft_putstr("Error\n");
	ft_putstr(msg);
	return (1);
}

void	exit_failure_closing_fd(char *s, int fd)
{
	exit_failure_with_error_message(s);
	close(fd);
	exit(EXIT_FAILURE);
}

int		get_resolution(t_data *data, char *r_line)
{
	size_t			index;
	const size_t	line_len = ft_strlen(r_line);

	mlx_get_screen_size(data->mlx, &data->map.window_width, &data->map.window_height);
	data->map.elements_num++;
	index = 0;
	while (index < line_len && r_line[index] == ' ')
		index++;
	if (index < line_len)
		data->map.window_width = MIN(data->map.window_width, ft_atoi(&r_line[index]));
	while (index < line_len && ft_isdigit(r_line[index]))
		index++;
	while (index < line_len && r_line[index] == ' ')
		index++;
	if (index < line_len)
		data->map.window_height = MIN(data->map.window_height, ft_atoi(&r_line[index]));
	while (index < line_len && ft_isdigit(r_line[index]))
		index++;
	if (index != line_len)
		// return (ERROR);
		return (0);
	// return (SUCCESS);
	return (1);
}

int		case_n(t_data *data, char *line)
{
	if (ft_strncmp(line, "./textures/redbrick.xpm", 23) == 0)
	{
		data->map.north_texture_path = ft_strdup("./textures/redbrick.xpm");
		return (1);
	}
	if (ft_strncmp(line, "./textures/greystone.xpm", 24) == 0)
	{
		data->map.north_texture_path = ft_strdup("./textures/greystone.xpm");
		return (1);
	}
	if (ft_strncmp(line, "./textures/bluestone.xpm", 24) == 0)
	{
		data->map.north_texture_path = ft_strdup("./textures/bluestone.xpm");
		return (1);
	}
	if (ft_strncmp(line, "./textures/colorstone.xpm", 25) == 0)
	{
		data->map.north_texture_path = ft_strdup("./textures/colorstone.xpm");
		return (1);
	}
	return (0);
}

int		get_texture_n(t_data *data, char *line)
{
	size_t			index;
	const size_t	line_len = ft_strlen(line);

	data->map.elements_num++;
	index = 0;
	while (line[index] == ' ')
		index++;
	// 予め存在するパスと一致しているかどうか。enum で実装できそう
	if (case_n(data, &line[index]) == 1)
		return (1);
	return (0);
}

int		case_e(t_data *data, char *line)
{
	if (ft_strncmp(line, "./textures/redbrick.xpm", 23) == 0)
	{
		data->map.east_texture_path = ft_strdup("./textures/redbrick.xpm");
		return (1);
	}
	if (ft_strncmp(line, "./textures/greystone.xpm", 24) == 0)
	{
		data->map.east_texture_path = ft_strdup("./textures/greystone.xpm");
		return (1);
	}
	if (ft_strncmp(line, "./textures/bluestone.xpm", 24) == 0)
	{
		data->map.east_texture_path = ft_strdup("./textures/bluestone.xpm");
		return (1);
	}
	if (ft_strncmp(line, "./textures/colorstone.xpm", 25) == 0)
	{
		data->map.east_texture_path = ft_strdup("./textures/colorstone.xpm");
		return (1);
	}
	return (0);
}

int		get_texture_e(t_data *data, char *line)
{
	size_t			index;
	const size_t	line_len = ft_strlen(line);

	data->map.elements_num++;
	index = 0;
	while (line[index] == ' ')
		index++;
	// 予め存在するパスと一致しているかどうか。enum で実装できそう
	if (case_e(data, &line[index]) == 1)
		return (1);
	return (0);
}


int		case_w(t_data *data, char *line)
{
	if (ft_strncmp(line, "./textures/redbrick.xpm", 23) == 0)
	{
		data->map.west_texture_path = ft_strdup("./textures/redbrick.xpm");
		return (1);
	}
	if (ft_strncmp(line, "./textures/greystone.xpm", 24) == 0)
	{
		data->map.west_texture_path = ft_strdup("./textures/greystone.xpm");
		return (1);
	}
	if (ft_strncmp(line, "./textures/bluestone.xpm", 24) == 0)
	{
		data->map.west_texture_path = ft_strdup("./textures/bluestone.xpm");
		return (1);
	}
	if (ft_strncmp(line, "./textures/colorstone.xpm", 25) == 0)
	{
		data->map.west_texture_path = ft_strdup("./textures/colorstone.xpm");
		return (1);
	}
	return (0);
}


int		get_texture_w(t_data *data, char *line)
{
	size_t			index;
	const size_t	line_len = ft_strlen(line);

	data->map.elements_num++;
	index = 0;
	while (line[index] == ' ')
		index++;
	// 予め存在するパスと一致しているかどうか。enum で実装できそう
	if (case_w(data, &line[index]) == 1)
		return (1);
	return (0);
}


int		case_s(t_data *data, char *line)
{
	if (ft_strncmp(line, "./textures/redbrick.xpm", 23) == 0)
	{
		data->map.south_texture_path = ft_strdup("./textures/redbrick.xpm");
		return (1);
	}
	if (ft_strncmp(line, "./textures/greystone.xpm", 24) == 0)
	{
		data->map.south_texture_path = ft_strdup("./textures/greystone.xpm");
		return (1);
	}
	if (ft_strncmp(line, "./textures/bluestone.xpm", 24) == 0)
	{
		data->map.south_texture_path = ft_strdup("./textures/bluestone.xpm");
		return (1);
	}
	if (ft_strncmp(line, "./textures/colorstone.xpm", 25) == 0)
	{
		data->map.south_texture_path = ft_strdup("./textures/colorstone.xpm");
		return (1);
	}
	return (0);
}


int		get_texture_s(t_data *data, char *line)
{
	size_t			index;
	const size_t	line_len = ft_strlen(line);

	data->map.elements_num++;
	index = 0;
	while (line[index] == ' ')
		index++;
	// 予め存在するパスと一致しているかどうか。enum で実装できそう
	if (case_s(data, &line[index]) == 1)
		return (1);
	return (0);
}

int		get_sprite(t_data *data, char *s_line)
{
	size_t	index;

	data->map.elements_num++;
	index = 0;
	while (s_line[index] == ' ')
		index++;
	if (ft_strncmp(s_line + index, "./textures/barrel.xpm", ft_strlen("./textures/barrel.xpm")) == 0)
	{
		data->map.sprite_texture_path = ft_strdup("./textures/barrel.xpm");
		return (1);
	}
	return (0);
}

int		get_colors_num(char *line, int *colors)
{
	size_t	s_i;
	size_t	l_i;

	s_i = 0;
	while (s_i < 3)
	{
		if (line[l_i] == ',')
			l_i++;
		colors[s_i] = ft_atoi(&line[l_i]);
		if (colors[s_i] > 255)
			return (ERROR);
		while (ft_isdigit(line[l_i]))
			l_i++;
		s_i++;
	}
	return (1);
}

int		set_color(t_data *data, char *line, char c)
{
	int	c_i;
	int l_i;
	int colors[3];

	c_i = 0;
	while (c_i < 3)
	{
		colors[c_i] = 0;
		c_i++;
	}
	l_i= 0;
	while (line[l_i] == ' ')
		l_i++;
	if (get_colors_num(&line[l_i], colors) == ERROR)
		return (0);
	if (c == 'F')
		data->map.floor_color = (colors[0] << 16) + (colors[1] << 8) + colors[2];
	else if (c == 'C')
		data->map.ceiling_color = (colors[0] << 16) + (colors[1] << 8) + colors[2];
	data->map.elements_num++;
	return (1);
}

bool	is_mapline(char *line)
{
	size_t	index;

	index = 0;
	while (line[index])
	{
		if (ft_isdigit(line[index]))
			return (true);
		index++;
	}
	return (false);
}

int		line_check(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '0' || line[i] == '1')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

// char	*ft_strjoin_with_br(char *map, char *line)
// {
// 	return (ft_strjoin(map, ft_strjoin(line, "\n")));
// }

char	*get_map_in(char *line, char *map)
{
	char	*tmp;

	if (line_check(line))
	{
		tmp = map;
		if (map == NULL)
			map = ft_strdup(line);
		else
			map = ft_strjoin(tmp, ft_strjoin(line, "\n"));
		if (map == NULL)
		{
			SAFE_FREE(tmp);
			return (NULL);
		}
		SAFE_FREE(tmp);
	}
	return (map);
}

void	get_player_info_and_sprite_num(t_data *data)
{
	int i;
	int j;

	i = 0;
	data->sprite_num = 0;
	data->player.p_x = 0;
	data->player.p_y = 0;
	while (data->w_map[i])
	{
		j = 0;
		while (data->w_map[i][j])
		{
			if (data->w_map[i][j] == '2')
				data->sprite_num++;
			if (data->w_map[i][j] == 'N' || data->w_map[i][j] == 'S' ||\
			data->w_map[i][j] == 'W' || data->w_map[i][j] == 'E')
			{
				data->player.p_x = j;
				data->player.p_y = i;
				data->player.dir = data->w_map[i][j];
			}
			j++;
		}
		i++;
	}
}

int		create_map_array(t_data *data, char *line)
{
	char	*map;
	char	*tmp;
	int		utils[3];
	size_t	map_rows;

	map = NULL;
	tmp = map;
	map_rows = 0;
	while ((utils[0] = get_next_line(data->fd, &line)) > 0)
	{
		if (line[0] == '\0')
			exit_putting_err_msg("invalid map\n", line);
		map = get_map_in(line, map);
		if (map_rows++ > 49 || ft_strlen(line) > 50)
			exit_putting_err_msg("The map is too large\n", line);
		SAFE_FREE(line);
	}
	map = get_map_in(line, map);
	// 特に '\n' である必要はない。そもそも、区切らずにどうにかできないのか。
	data->w_map = ft_split(map, '\n');
	data->w_map_c = ft_split(map, '\n');
	SAFE_FREE(map);
	get_player_info_and_sprite_num(data);
	SAFE_FREE(line);
	return (1);
}

int		get_line_data(t_data *data, char *line)
{
	// return (0) ならエラーのはず
	if (ft_strncmp(line, "R ", 2) == 0)
		return (get_resolution(data, &line[1]));
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (get_texture_n(data, &line[2]));
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (get_texture_s(data, &line[2]));
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (get_texture_w(data, &line[2]));
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (get_texture_e(data, &line[2]));
	if (ft_strncmp(line, "S ", 2) == 0)
		return (get_sprite(data, &line[1]));
	if (ft_strncmp(line, "F ", 2) == 0)
		return (set_color(data, &line[1], 'F'));
	if (ft_strncmp(line, "C ", 2) == 0)
		return (set_color(data, &line[1], 'C'));
	if (is_mapline(line) == true)
		return (create_map_array(data, line));
	return (1);
}

void	free_map(t_data *data)
{
	int index;

	index = 0;
	while (data->w_map[index])
	{
		SAFE_FREE(data->w_map[index]);
		index++;
	}
	index = 0;
	while (data->w_map_c[index])
	{
		SAFE_FREE(data->w_map_c[index]);
		index++;
	}
}
// 各チェック関数の最初に、NOT_SETじゃない場合はエラーにする処理を加える。ここでチェックするのは、elements_num だけで良い。
void	map_elements_check(t_data *data)
{
	if (data->map.window_width == 0 || data->map.window_height == 0\
	|| data->map.north_texture_path == NULL)
	{
		free_map(data);
		exit_failure_with_error_message("elements\n");
		exit(0);
	}
	if (data->map.south_texture_path == NULL || data->map.west_texture_path == NULL)
	{
		free_map(data);
		exit_failure_with_error_message("elements\n");
		exit(0);
	}
	if (data->map.east_texture_path == NULL || data->map.sprite_texture_path == NULL\
	|| data->map.elements_num != 8)
	{
		free_map(data);
		exit_failure_with_error_message("elements\n");
		exit(0);
	}
}

void	get_sprite_pos(t_data *data)
{
	int x;
	int y;
	int s_i;

	x = 0;
	s_i = 0;
	while (data->w_map[x])
	{
		y = 0;
		while (data->w_map[x][y])
		{
			if (data->w_map[x][y] == '2')
			{
				data->sprite[s_i].x = y;
				data->sprite[s_i].y = x;
				s_i++;
			}
			y++;
		}
		x++;
	}
}

void	fill(t_data *data, int y, int x, int index)
{
	if (y < 0 || y >= index || x < 0 || data->w_map_c[y][x] == ' ')
		return ;
	if (data->w_map_c[y][x] == '1')
		return ;
	if (data->w_map_c[y][x] != 'N' && data->w_map_c[y][x] != 'E' && data->w_map_c[y][x] != 'W' && data->w_map_c[y][x] != 'S' && data->w_map_c[y][x] != '0' && data->w_map_c[y][x] != '2')
		return ;
	if (data->err_flag == true)
		return ;
	if (y == 0 || x == 0 || y == index || x == (int)(ft_strlen(data->w_map_c[y]) - 1))
		data->err_flag = true;

	data->w_map_c[y][x] = 'X';
	fill(data, y + 1, x, index);
	fill(data, y - 1, x, index);
	fill(data, y, x + 1, index);
	fill(data, y, x - 1, index);
}

void	check(t_data *data)
{
	int	index;

	index = 0;
	data->err_flag = false;
	while (data->w_map_c[index])
		index++;
	fill(data, (int)data->player.p_y, (int)data->player.p_x, index);
	index = 0;
	if (data->err_flag == true)
	{
		exit_failure_with_error_message("invalid map\n");
		exit(0);
	}
}

void	get_line_data(t_data *data, char *filename)
{
	char	*line;
	int		rc;

	init_map(data);
	if ((data->fd = open(filename, O_RDONLY)) == ERROR)
		exit_failure_closing_fd("could not open file", data->fd);
	rc = 0;
	while (get_next_line(data->fd, &line) > 0)
	{
		rc = get_line_data(data, line);
		if (rc == ERROR)
			data->err_flag = true;
		SAFE_FREE(line);
	}
	SAFE_FREE(line);
	map_elements_check(data);
	data->sprite = malloc(sizeof(t_sprite) * data->sprite_num);
	if (data->err_flag == true)
	{
		free_map(data);
		exit_failure_with_error_message("map");
		exit(0);
	}
	get_sprite_pos(data);
	check(data);
}

void	set_player_pos_n_dir_2(t_data *data)
{
	if (data->player.dir == 'N')
	{
		data->player.dir_x = 0;
		data->player.dir_y = -1;
		data->player.pl_x = -0.66;
		data->player.pl_y = 0;
	}
	else if (data->player.dir == 'S')
	{
		data->player.dir_x = 0;
		data->player.dir_y = 1;
		data->player.pl_x = 0.66;
		data->player.pl_y = 0;
	}
}


void	set_player_pos_n_dir(t_data *data)
{
	if (data->player.dir == 'W')
	{
		data->player.dir_x = -1;
		data->player.dir_y = 0;
		data->player.pl_x = 0;
		data->player.pl_y = 0.66;
	}
	else if (data->player.dir == 'E')
	{
		data->player.dir_x = 1;
		data->player.dir_y = 0;
		data->player.pl_x = 0;
		data->player.pl_y = -0.66;
	}
	else if (data->player.dir == 'S')
	{
		set_player_pos_n_dir_2(data);
	}
	else if (data->player.dir == 'N')
	{
		set_player_pos_n_dir_2(data);
	}
}

void	set_player_info(t_data *data)
{
	set_player_pos_n_dir(data);
	data->player.spd = 0.05;
	data->player.rl_spd = 0.05;
}

void	init_keys_status(t_data *data)
{
	data->key.fd = 0;
	data->key.bk = 0;
	data->key.lt = 0;
	data->key.rt = 0;
	data->key.rrt = 0;
	data->key.rlt = 0;
}

int		tex(t_data *data)
{
	int x;

	if (!(data->tex[WALL_N].img_ptr = mlx_xpm_file_to_image(data->mlx,\
	data->map.north_texture_path, &data->tex[WALL_N].w, &data->tex[WALL_N].h)))
		return (0);
	data->tex[WALL_N].addr = mlx_get_data_addr(data->tex[WALL_N].img_ptr,\
	&data->tex[WALL_N].b_per_pix, &data->tex[WALL_N].line_length,\
	&data->tex[0].endian);
	if (!(data->tex[WALL_S].img_ptr = mlx_xpm_file_to_image(data->mlx,\
	data->map.south_texture_path, &data->tex[WALL_S].w, &data->tex[WALL_S].h)))
		return (0);
	data->tex[WALL_S].addr = mlx_get_data_addr(data->tex[WALL_S].img_ptr,\
	&data->tex[WALL_S].b_per_pix, &data->tex[WALL_S].line_length,\
	&data->tex[0].endian);
	if (!(data->tex[WALL_E].img_ptr = mlx_xpm_file_to_image(data->mlx,\
	data->map.east_texture_path, &data->tex[WALL_E].w, &data->tex[WALL_E].h)))
		return (0);
	data->tex[WALL_E].addr = mlx_get_data_addr(data->tex[WALL_E].img_ptr,\
	&data->tex[WALL_E].b_per_pix, &data->tex[WALL_E].line_length,\
	&data->tex[0].endian);
	x = tex_etc(data);
	if (x == 0)
		return (0);
	return (1);
}

void	init_elements(t_data *data)
{
	data->mlx = mlx_init();
	data->data = mlx_new_image(data->mlx, data->map.window_width, data->map.window_height);
	data->addr = mlx_get_data_addr(data->data, &data->bits_per_pixel, &data->line_length, &data->endian);
	data->win = mlx_new_window(data->mlx, data->map.window_width, data->map.window_height, "cub3d_monoue");
	set_player_info(data);
	init_keys_status(data);
	tex(data);
}

void	init_game(char *filename)
{
	t_data	data;

	get_line_data(&data, filename);
	if (data.w_map[(int)data.player.p_y][(int)data.player.p_x + 1] == '1' || data.w_map[(int)data.player.p_y][(int)data.player.p_x + 1] == '1' || data.w_map[(int)data.player.p_y][(int)data.player.p_x + 1] == '1' || data.w_map[(int)data.player.p_y - 1][(int)data.player.p_x] == '1')
	{
		free_map(&data);
		exit_failure_with_error_message("player position\n");
		exit(0);
	}
	init_elements(&data);
}