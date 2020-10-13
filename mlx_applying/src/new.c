#include "new.h"

int		put_err_msg(char *msg)
{
	ft_putstr("Error\n");
	ft_putstr(msg);
	return (0);
}

void	map_open_error(char *s, int fd)
{
	put_err_msg(s);
	close(fd);
	exit(EXIT_SUCCESS);
}

int		get_window(t_data *img, char *r_line)
{
	size_t			index;
	const size_t	line_len = ft_strlen(r_line);

	mlx_get_screen_size(img->mlx, &img->map.screen_w, &img->map.screen_h);
	img->map.elements_num++;
	index = 0;
	while (index < line_len && r_line[index] == ' ')
		index++;
	if (index < line_len)
		img->map.screen_w = MIN(img->map.screen_w, ft_atoi(&r_line[index]));
	while (index < line_len && ft_isdigit(r_line[index]))
		index++;
	while (index < line_len && r_line[index] == ' ')
		index++;
	if (index < line_len)
		img->map.screen_h = MIN(img->map.screen_h, ft_atoi(&r_line[index]));
	while (index < line_len && ft_isdigit(r_line[index]))
		index++;
	if (index != line_len)
		// return (ERROR);
		return (0);
	// return (SUCCESS);
	return (1);
}

int		case_n(t_data *img, char *line)
{
	if (ft_strncmp(line, "./textures/redbrick.xpm", 23) == 0)
	{
		img->map.n_texture = ft_strdup("./textures/redbrick.xpm");
		return (1);
	}
	if (ft_strncmp(line, "./textures/greystone.xpm", 24) == 0)
	{
		img->map.n_texture = ft_strdup("./textures/greystone.xpm");
		return (1);
	}
	if (ft_strncmp(line, "./textures/bluestone.xpm", 24) == 0)
	{
		img->map.n_texture = ft_strdup("./textures/bluestone.xpm");
		return (1);
	}
	if (ft_strncmp(line, "./textures/colorstone.xpm", 25) == 0)
	{
		img->map.n_texture = ft_strdup("./textures/colorstone.xpm");
		return (1);
	}
	return (0);
}

int		get_texture_n(t_data *img, char *line)
{
	size_t			index;
	const size_t	line_len = ft_strlen(line);

	img->map.elements_num++;
	index = 0;
	while (line[index] == ' ')
		index++;
	// 予め存在するパスと一致しているかどうか。enum で実装できそう
	if (case_n(img, &line[index]) == 1)
		return (1);
	return (0);
}

int		case_e(t_data *img, char *line)
{
	if (ft_strncmp(line, "./textures/redbrick.xpm", 23) == 0)
	{
		img->map.e_texture = ft_strdup("./textures/redbrick.xpm");
		return (1);
	}
	if (ft_strncmp(line, "./textures/greystone.xpm", 24) == 0)
	{
		img->map.e_texture = ft_strdup("./textures/greystone.xpm");
		return (1);
	}
	if (ft_strncmp(line, "./textures/bluestone.xpm", 24) == 0)
	{
		img->map.e_texture = ft_strdup("./textures/bluestone.xpm");
		return (1);
	}
	if (ft_strncmp(line, "./textures/colorstone.xpm", 25) == 0)
	{
		img->map.e_texture = ft_strdup("./textures/colorstone.xpm");
		return (1);
	}
	return (0);
}

int		get_texture_e(t_data *img, char *line)
{
	size_t			index;
	const size_t	line_len = ft_strlen(line);

	img->map.elements_num++;
	index = 0;
	while (line[index] == ' ')
		index++;
	// 予め存在するパスと一致しているかどうか。enum で実装できそう
	if (case_e(img, &line[index]) == 1)
		return (1);
	return (0);
}


int		case_w(t_data *img, char *line)
{
	if (ft_strncmp(line, "./textures/redbrick.xpm", 23) == 0)
	{
		img->map.w_texture = ft_strdup("./textures/redbrick.xpm");
		return (1);
	}
	if (ft_strncmp(line, "./textures/greystone.xpm", 24) == 0)
	{
		img->map.w_texture = ft_strdup("./textures/greystone.xpm");
		return (1);
	}
	if (ft_strncmp(line, "./textures/bluestone.xpm", 24) == 0)
	{
		img->map.w_texture = ft_strdup("./textures/bluestone.xpm");
		return (1);
	}
	if (ft_strncmp(line, "./textures/colorstone.xpm", 25) == 0)
	{
		img->map.w_texture = ft_strdup("./textures/colorstone.xpm");
		return (1);
	}
	return (0);
}


int		get_texture_w(t_data *img, char *line)
{
	size_t			index;
	const size_t	line_len = ft_strlen(line);

	img->map.elements_num++;
	index = 0;
	while (line[index] == ' ')
		index++;
	// 予め存在するパスと一致しているかどうか。enum で実装できそう
	if (case_w(img, &line[index]) == 1)
		return (1);
	return (0);
}


int		case_s(t_data *img, char *line)
{
	if (ft_strncmp(line, "./textures/redbrick.xpm", 23) == 0)
	{
		img->map.s_texture = ft_strdup("./textures/redbrick.xpm");
		return (1);
	}
	if (ft_strncmp(line, "./textures/greystone.xpm", 24) == 0)
	{
		img->map.s_texture = ft_strdup("./textures/greystone.xpm");
		return (1);
	}
	if (ft_strncmp(line, "./textures/bluestone.xpm", 24) == 0)
	{
		img->map.s_texture = ft_strdup("./textures/bluestone.xpm");
		return (1);
	}
	if (ft_strncmp(line, "./textures/colorstone.xpm", 25) == 0)
	{
		img->map.s_texture = ft_strdup("./textures/colorstone.xpm");
		return (1);
	}
	return (0);
}


int		get_texture_s(t_data *img, char *line)
{
	size_t			index;
	const size_t	line_len = ft_strlen(line);

	img->map.elements_num++;
	index = 0;
	while (line[index] == ' ')
		index++;
	// 予め存在するパスと一致しているかどうか。enum で実装できそう
	if (case_s(img, &line[index]) == 1)
		return (1);
	return (0);
}

int		get_sprite(t_data *img, char *s_line)
{
	size_t	index;

	img->map.elements_num++;
	index = 0;
	while (s_line[index] == ' ')
		index++;
	if (ft_strncmp(s_line + index, "./textures/barrel.xpm", ft_strlen("./textures/barrel.xpm")) == 0)
	{
		img->map.sprite_texture = ft_strdup("./textures/barrel.xpm");
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

int		get_colors(t_data *img, char *line, char c)
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
		img->map.floor_color = (colors[0] << 16) + (colors[1] << 8) + colors[2];
	else if (c == 'C')
		img->map.ceiling_color = (colors[0] << 16) + (colors[1] << 8) + colors[2];
	img->map.elements_num++;
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

void	get_player_info_and_sprite_num(t_data *img)
{
	int i;
	int j;

	i = 0;
	img->sprite_num = 0;
	img->player.p_x = 0;
	img->player.p_y = 0;
	while (img->w_map[i])
	{
		j = 0;
		while (img->w_map[i][j])
		{
			if (img->w_map[i][j] == '2')
				img->sprite_num++;
			if (img->w_map[i][j] == 'N' || img->w_map[i][j] == 'S' ||\
			img->w_map[i][j] == 'W' || img->w_map[i][j] == 'E')
			{
				img->player.p_x = j;
				img->player.p_y = i;
				img->player.dir = img->w_map[i][j];
			}
			j++;
		}
		i++;
	}
}

int		get_map(t_data *img, char *line)
{
	char	*map;
	char	*tmp;
	int		utils[3];
	size_t	map_rows;

	map = NULL;
	tmp = map;
	map_rows = 0;
	while ((utils[0] = get_next_line(img->fd, &line)) > 0)
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
	img->w_map = ft_split(map, '\n');
	img->w_map_c = ft_split(map, '\n');
	SAFE_FREE(map);
	get_player_info_and_sprite_num(img);
	SAFE_FREE(line);
	return (1);
}

int		get_map_info(t_data *img, char *line)
{
	// return (0) ならエラーのはず
	if (ft_strncmp(line, "R ", 2) == 0)
		return (get_window(img, &line[1]));
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (get_texture_n(img, &line[2]));
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (get_texture_s(img, &line[2]));
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (get_texture_w(img, &line[2]));
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (get_texture_e(img, &line[2]));
	if (ft_strncmp(line, "S ", 2) == 0)
		return (get_sprite(img, &line[1]));
	if (ft_strncmp(line, "F ", 2) == 0)
		return (get_colors(img, &line[1], 'F'));
	if (ft_strncmp(line, "C ", 2) == 0)
		return (get_colors(img, &line[1], 'C'));
	if (is_mapline(line) == true)
		return (get_map(img, line));
	return (1);
}

void	free_map(t_data *img)
{
	int index;

	index = 0;
	while (img->w_map[index])
	{
		SAFE_FREE(img->w_map[index]);
		index++;
	}
	index = 0;
	while (img->w_map_c[index])
	{
		SAFE_FREE(img->w_map_c[index]);
		index++;
	}
}
// 各チェック関数の最初に、NOT_SETじゃない場合はエラーにする処理を加える。ここでチェックするのは、elements_num だけで良い。
void	map_elements_check(t_data *img)
{
	if (img->map.screen_w == 0 || img->map.screen_h == 0\
	|| img->map.n_texture == NULL)
	{
		free_map(img);
		put_err_msg("elements\n");
		exit(0);
	}
	if (img->map.s_texture == NULL || img->map.w_texture == NULL)
	{
		free_map(img);
		put_err_msg("elements\n");
		exit(0);
	}
	if (img->map.e_texture == NULL || img->map.sprite_texture == NULL\
	|| img->map.elements_num != 8)
	{
		free_map(img);
		put_err_msg("elements\n");
		exit(0);
	}
}

void	get_sprite_pos(t_data *img)
{
	int x;
	int y;
	int s_i;

	x = 0;
	s_i = 0;
	while (img->w_map[x])
	{
		y = 0;
		while (img->w_map[x][y])
		{
			if (img->w_map[x][y] == '2')
			{
				img->sprite[s_i].x = y;
				img->sprite[s_i].y = x;
				s_i++;
			}
			y++;
		}
		x++;
	}
}

void	fill(t_data *img, int y, int x, int index)
{
	if (y < 0 || y >= index || x < 0 || img->w_map_c[y][x] == ' ')
		return ;
	if (img->w_map_c[y][x] == '1')
		return ;
	if (img->w_map_c[y][x] != 'N' && img->w_map_c[y][x] != 'E' && img->w_map_c[y][x] != 'W' && img->w_map_c[y][x] != 'S' && img->w_map_c[y][x] != '0' && img->w_map_c[y][x] != '2')
		return ;
	if (img->err_flag == true)
		return ;
	if (y == 0 || x == 0 || y == index || x == (int)(ft_strlen(img->w_map_c[y]) - 1))
		img->err_flag = true;

	img->w_map_c[y][x] = 'X';
	fill(img, y + 1, x, index);
	fill(img, y - 1, x, index);
	fill(img, y, x + 1, index);
	fill(img, y, x - 1, index);
}

void	check(t_data *img)
{
	int	index;

	index = 0;
	img->err_flag = false;
	while (img->w_map_c[index])
		index++;
	fill(img, (int)img->player.p_y, (int)img->player.p_x, index);
	index = 0;
	if (img->err_flag == true)
	{
		put_err_msg("invalid map\n");
		exit(0);
	}
}

void	read_map_open(t_data *img, char *filename)
{
	char	*line;
	int		rc;

	init_map(img);
	if ((img->fd = open(filename, O_RDONLY)) == ERROR)
		map_open_error("could not open file", img->fd);
	rc = 0; // rv???
	while (get_next_line(img->fd, &line) > 0)
	{
		rc = get_map_info(img, line);
		// ここまで
		if (rc == ERROR)
			img->err_flag = true;
		SAFE_FREE(line);
	}
	SAFE_FREE(line);
	map_elements_check(img);
	img->sprite = malloc(sizeof(t_sprite) * img->sprite_num);
	if (img->err_flag == true)
	{
		free_map(img);
		put_err_msg("map");
		exit(0);
	}
	get_sprite_pos(img);
	check(img);
}

void	set_player_pos_n_dir_2(t_data *img)
{
	if (img->player.dir == 'N')
	{
		img->player.dir_x = 0;
		img->player.dir_y = -1;
		img->player.pl_x = -0.66;
		img->player.pl_y = 0;
	}
	else if (img->player.dir == 'S')
	{
		img->player.dir_x = 0;
		img->player.dir_y = 1;
		img->player.pl_x = 0.66;
		img->player.pl_y = 0;
	}
}


void	set_player_pos_n_dir(t_data *img)
{
	if (img->player.dir == 'W')
	{
		img->player.dir_x = -1;
		img->player.dir_y = 0;
		img->player.pl_x = 0;
		img->player.pl_y = 0.66;
	}
	else if (img->player.dir == 'E')
	{
		img->player.dir_x = 1;
		img->player.dir_y = 0;
		img->player.pl_x = 0;
		img->player.pl_y = -0.66;
	}
	else if (img->player.dir == 'S')
	{
		set_player_pos_n_dir_2(img);
	}
	else if (img->player.dir == 'N')
	{
		set_player_pos_n_dir_2(img);
	}
}

void	set_player_info(t_data *img)
{
	set_player_pos_n_dir(img);
	img->player.spd = 0.05;
	img->player.rl_spd = 0.05;
}

void	init_keys_status(t_data *img)
{
	img->key.fd = 0;
	img->key.bk = 0;
	img->key.lt = 0;
	img->key.rt = 0;
	img->key.rrt = 0;
	img->key.rlt = 0;
}

int		tex(t_data *img)
{
	int x;

	if (!(img->tex[WALL_N].img_ptr = mlx_xpm_file_to_image(img->mlx,\
	img->map.n_texture, &img->tex[WALL_N].w, &img->tex[WALL_N].h)))
		return (0);
	img->tex[WALL_N].addr = mlx_get_data_addr(img->tex[WALL_N].img_ptr,\
	&img->tex[WALL_N].b_per_pix, &img->tex[WALL_N].line_length,\
	&img->tex[0].endian);
	if (!(img->tex[WALL_S].img_ptr = mlx_xpm_file_to_image(img->mlx,\
	img->map.s_texture, &img->tex[WALL_S].w, &img->tex[WALL_S].h)))
		return (0);
	img->tex[WALL_S].addr = mlx_get_data_addr(img->tex[WALL_S].img_ptr,\
	&img->tex[WALL_S].b_per_pix, &img->tex[WALL_S].line_length,\
	&img->tex[0].endian);
	if (!(img->tex[WALL_E].img_ptr = mlx_xpm_file_to_image(img->mlx,\
	img->map.e_texture, &img->tex[WALL_E].w, &img->tex[WALL_E].h)))
		return (0);
	img->tex[WALL_E].addr = mlx_get_data_addr(img->tex[WALL_E].img_ptr,\
	&img->tex[WALL_E].b_per_pix, &img->tex[WALL_E].line_length,\
	&img->tex[0].endian);
	x = tex_etc(img);
	if (x == 0)
		return (0);
	return (1);
}

void	init_elements(t_data *img)
{
	img->mlx = mlx_init();
	img->img = mlx_new_image(img->mlx, img->map.screen_w, img->map.screen_h);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	img->mlx_win = mlx_new_window(img->mlx, img->map.screen_w, img->map.screen_h, "cub3d_monoue");
	set_player_info(img);
	init_keys_status(img);
	tex(img);
}

void	init_game(char *filename)
{
	t_data	img;

	read_map_open(&img, filename);
	if (img.w_map[(int)img.player.p_y][(int)img.player.p_x + 1] == '1' || img.w_map[(int)img.player.p_y][(int)img.player.p_x + 1] == '1' || img.w_map[(int)img.player.p_y][(int)img.player.p_x + 1] == '1' || img.w_map[(int)img.player.p_y - 1][(int)img.player.p_x] == '1')
	{
		free_map(&img);
		put_err_msg("player position\n");
		exit(0);
	}
	init_elements(&img);
}