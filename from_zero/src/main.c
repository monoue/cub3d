#include "../minilibx/mlx_beta/mlx.h"

#include "libft/libft.h"
#include "main.h"
#include "player.h"


// こんな感じ？
// const char *g_texture_file_names[TEXTURES_NUM] =
// {
// 	BLUESTONE_XPM,
// 	BARREL_XPM,
// 	COLORSTONE_XPM,
// 	GREYSTONE_XPM,
// 	REDBRICK_XPM
// };
// const char *g_ids[ID_NUM] =
// {
// 	"R",
// 	"NO",
// 	"EA",
// 	"WE",
// 	"SO",
// 	"S",
// 	"F",
// 	"C",
// };

void	exit_with_error_message(t_error_types message_type,  char *error_content)
// int		exit_with_error_message(char *error_content)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	if (message_type == ERRNO)
		perror(NULL);
	else if (message_type == SINGLE)
		ft_putstr_fd(error_content, STDERR_FILENO);
	else if (message_type == ID_OVERLAPPING)
	{
		ft_putstr_fd(".cub file has more than one \"", STDERR_FILENO);
		ft_putstr_fd(error_content, STDERR_FILENO);
		ft_putstr_fd("\" lines.\n", STDERR_FILENO);
	}
	else if (message_type == WRONG_INFO_NUM)
	{
		ft_putstr_fd(".cub file: \"", STDERR_FILENO);
		ft_putstr_fd(error_content, STDERR_FILENO);
		ft_putstr_fd("\" line's informations' number is wrong.\n", STDERR_FILENO);
	}
	else if (message_type == INVALID_INFO)
	{
		ft_putstr_fd(".cub file: \"", STDERR_FILENO);
		ft_putstr_fd(error_content, STDERR_FILENO);
		ft_putstr_fd("\" line's informations is invalid.\n", STDERR_FILENO);
	}
	// TODO: これって、今まだ使っているんだっけ？
	// ERRNO で対応できないかな？
	else if (message_type == INVALID_PATH)
	{
		ft_putstr_fd(".cub file: \"", STDERR_FILENO);
		ft_putstr_fd(error_content, STDERR_FILENO);
		ft_putstr_fd("\" line's path is invalid.\n", STDERR_FILENO);
	}
	else if (message_type == LACKING_ELEMENT)
	{
		ft_putstr_fd(".cub file: \"", STDERR_FILENO);
		ft_putstr_fd(error_content, STDERR_FILENO);
		ft_putstr_fd("\" line is lacking.\n", STDERR_FILENO);
	}
	// TODO: fd の close もここでやる？　だとすれば、fd はグローバル変数？
	exit(EXIT_FAILURE);
}

#include <string.h>

// void	map_init(t_data *data)
// {
// 	data->map.window_width = NOT_SET;
// 	data->map.window_height = NOT_SET;
// 	data->map.north_texture_path = NULL;
// 	data->map.south_texture_path = NULL;
// 	data->map.west_texture_path = NULL;
// 	data->map.east_texture_path = NULL;
// 	data->map.sprite_texture_path = NULL;
// 	data->map.floor_color = NOT_SET;
// 	data->map.ceiling_color = NOT_SET;
// 	data->err_flag = false;
// }

// t_cubfile_data g_cubfile_data;

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

t_data g_data;

// void	exit_failure_closing_fd(int fd)
// {
// 	ft_putstr_fd(".cub file could not be opened.\n", STDERR_FILENO);
// 	close(fd);
// 	exit(EXIT_FAILURE);
// }

bool	ft_str_is_numeric(const char *str)
{
	size_t	index;

	index = 0;
	while (str[index] != '\0' && ft_isdigit(str[index]))
		index++;
	return (index == ft_strlen(str));
}

size_t	ft_count_strs(const char **strs)
{
	size_t	count;

	count = 0;
	while (strs[count] != NULL)
		count++;
	return (count);
}

void	get_resolution(const char **infos)
{
	if (!(g_cubfile_data.window_width == NOT_SET && g_cubfile_data.window_height == NOT_SET))
		exit_with_error_message(ID_OVERLAPPING, "R");
	if (ft_count_strs(infos) != 2)
		exit_with_error_message(WRONG_INFO_NUM, "R");
	if (!ft_str_is_numeric(infos[0]) || !ft_str_is_numeric(infos[1]))
		exit_with_error_message(INVALID_INFO, "R");
	mlx_get_screen_size(g_data.mlx, &g_cubfile_data.window_width, &g_cubfile_data.window_height);
	g_cubfile_data.window_width = MIN(g_cubfile_data.window_width, ft_atoi(infos[0]));
	g_cubfile_data.window_height = MIN(g_cubfile_data.window_height, ft_atoi(infos[1]));
	if (g_cubfile_data.window_width == 0 || g_cubfile_data.window_height == 0)
		exit_with_error_message(INVALID_INFO, "R");
	// printf("%d, %d\n", g_cubfile_data.window_width, g_cubfile_data.window_height);
}

void	set_texture(char **texture_path, const char **infos, char *id)
{
	size_t			texture_i;

	if (*texture_path != NULL)
		exit_with_error_message(ID_OVERLAPPING, id);
	if (ft_count_strs(infos) != 1)
		exit_with_error_message(WRONG_INFO_NUM, id);
	texture_i = 0;
	// printf("%s\n", g_texture_file_names[GREYSTONE]);
	// printf("%s\n", infos[0]);
	while (texture_i < TEXTURES_NUM)
	{
		if (ft_strcmp(id, "NO") == 0)
			g_cubfile_data.north_texture_path = ft_strdup(infos[0]);
		else if (ft_strcmp(id, "EA") == 0)
			g_cubfile_data.east_texture_path = ft_strdup(infos[0]);
		else if (ft_strcmp(id, "WE") == 0)
			g_cubfile_data.west_texture_path = ft_strdup(infos[0]);
		else if (ft_strcmp(id, "SO") == 0)
			g_cubfile_data.south_texture_path = ft_strdup(infos[0]);
		else if (ft_strcmp(id, "S") == 0)
			g_cubfile_data.sprite_texture_path = ft_strdup(infos[0]);
		break ;
		texture_i++;
	}
	if (texture_i == TEXTURES_NUM)
		exit_with_error_message(INVALID_PATH, id);
	// printf("%s\n", g_cubfile_data.north_texture_path);
}

bool	is_out_of_color_range(int trgb_element)
{
	return (trgb_element < 0 || trgb_element > 255);
}

size_t	count_specific_c(const char *str, char c)
{
	size_t	index;
	size_t	c_count;

	c_count = 0;
	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] == c)
			c_count++;
		index++;
	}
	return (c_count);
}

void	exit_if_color_line_is_invalid(t_color color, const char **infos, const char **num_strs, char *id)
{
	size_t	index;

	if (color != NOT_SET)
		exit_with_error_message(ID_OVERLAPPING, id);
	if (ft_count_strs(infos) != 1)
		exit_with_error_message(WRONG_INFO_NUM, id);
	if (count_specific_c(infos[0], ',') != 2 || ft_count_strs(num_strs) != 3)
		exit_with_error_message(INVALID_INFO, id);
	index = 0;
	while (index < 3)
	{
		if (!ft_str_is_numeric(num_strs[index]))
			exit_with_error_message(INVALID_INFO, id);
		index++;
	}
}

t_color	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}


void	set_color(t_color *color, const char **infos, char *id)
{
	const char	**num_strs = (const char **)ft_split(infos[0], ',');
	size_t		rgb_index;
	int			rgb_elements[3];

	exit_if_color_line_is_invalid(*color, infos, num_strs, id);
	rgb_index = 0;
	while (rgb_index < 3)
	{
		rgb_elements[rgb_index] = ft_atoi(num_strs[rgb_index]);
		if (is_out_of_color_range(rgb_elements[rgb_index]))
			exit_with_error_message(INVALID_INFO, id);
		rgb_index++;
	}
	*color = create_trgb(0, rgb_elements[0], rgb_elements[1], rgb_elements[2]);
}

bool	is_spawn_point_c(char c)
{
	return (c == 'N' || c == 'E' || c == 'W' || c == 'S');
}

bool	is_map_c(char c)
{
	return ((c >= '0' && c <= '2') || is_spawn_point_c(c) || c == ' ');
}
// 1) スペースをスキップ
// 2) そ時時点で '\0' だったら false
// 3) map_c もしくは スペースの間スキップ
// 4) \0 だったら tru
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

char	g_map[MAX_MAP_LEN + 1][MAX_MAP_LEN + 1] = {'\0'};
char	g_map_to_check[MAX_MAP_LEN + 1][MAX_MAP_LEN + 1] = {'\0'};

bool	all_elements_are_set(void)
{
	return (!(g_cubfile_data.window_width == NOT_SET
	|| g_cubfile_data.window_height == NOT_SET
	|| g_cubfile_data.north_texture_path == NULL
	|| g_cubfile_data.east_texture_path == NULL
	|| g_cubfile_data.west_texture_path == NULL
	|| g_cubfile_data.south_texture_path == NULL
	|| g_cubfile_data.sprite_texture_path == NULL
	|| g_cubfile_data.floor_color == NOT_SET
	|| g_cubfile_data.ceiling_color == NOT_SET));
}

void	map_exit_failure(char *line, char *error_message)
{
	free(line);
	free(g_map);
	exit_with_error_message(SINGLE, error_message);
}

bool	is_empty_line(char *line)
{
	size_t	index;

	index = 0;
	while (line[index] == ' ')
		index++;
	return (line[index] == '\0');
}

// void	add_line_with_br(char **joined_map_str, char *map_line)
// {
// 	char *tmp;

// 	tmp = *joined_map_str;
// 	*joined_map_str = ft_strjoin(*joined_map_str, "\n");
// 	SAFE_FREE(tmp);
// 	tmp = *joined_map_str;
// 	*joined_map_str = ft_strjoin(*joined_map_str, map_line);
// 	SAFE_FREE(tmp);
// 	g_cubfile_data.map_height++;
// }

void	exit_if_too_large_map(char *cubfile_line)
{
	if (g_cubfile_data.map_height > MAX_MAP_LEN - 1)
		map_exit_failure(cubfile_line, ".cub file: The map is too high.\n");
	if (ft_strlen(cubfile_line) > MAX_MAP_LEN)
		map_exit_failure(cubfile_line, ".cub file: The map is too wide.\n");
}

float	get_spawning_angle(char c)
{
	if (c == 'E')
		return (0);
	if (c == 'S')
		return (PI * 0.5);
	if (c == 'W')
		return (PI);
	if (c == 'N')
		return (PI * 1.5);
}

bool	map_has_double_spawn_points()
{
	return (!(g_player.x == NOT_SET));
}

void	set_player_spawning_data(char x, char y, char current_c)
{
	g_player.x = (float)CTOI(x);
	g_player.y = (float)CTOI(y);
	g_player.rotation_angle = get_spawning_angle(current_c);
}

void	set_spawn_data_and_sprites_num(t_data *data)
{
	size_t	y;
	size_t	x;
	char	current_c;

	g_cubfile_data.sprites_num = 0;
	y = 0;
	while (g_map[y] != NULL)
	{
		x = 0;
		while (g_map[y][x] != '\0')
		{
			current_c = g_map[y][x];
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

// TODO: ft_strcpy 作成
void	copy_line_to_map(const char *cubfile_line, size_t current_row)
{
	ft_strcpy(g_map[current_row], cubfile_line);
	ft_strcpy(g_map_to_check[current_row], cubfile_line);
}

void	create_map_array(t_data *data, char *map_first_line, int fd)
{
	char	*joined_map_str;
	char	*cubfile_line;
	size_t	current_row;

	copy_line_to_map(map_first_line, 0);
	current_row = 1;
	// joined_map_str = ft_strdup_free(map_first_line);
	while (get_next_line(fd, &cubfile_line) > 0)
	{
		if (is_empty_line(cubfile_line))
			while (get_next_line(fd, &cubfile_line) > 0)
				if (!is_empty_line(cubfile_line))
					map_exit_failure(cubfile_line, ".cub file: The map has empty lines.\n");
		else
		{
			exit_if_too_large_map(cubfile_line);
			copy_line_to_map(cubfile_line, current_row);
			// add_line_with_br(&joined_map_str, cubfile_line);
			SAFE_FREE(cubfile_line);
			current_row++;
		}
		// if (g_cubfile_data.map_height > MAX_MAP_LENGTH || ft_strlen(cubfile_line) > MAX_MAP_LENGTH)
		// {
		// 	DEBUGVD((int)g_cubfile_data.map_height);
		// 	DEBUGVD((int)ft_strlen(cubfile_line));
			// map_exit_failure(cubfile_line, ".cub file: The map is too large.\n");
		// }

	}
	exit_if_too_large_map(cubfile_line);
	copy_line_to_map(cubfile_line, current_row);
	// add_line_with_br(&joined_map_str, cubfile_line);
	// g_map_to_check = ft_split(joined_map_str, '\n');
	// g_map = ft_split(joined_map_str, '\n');
	SAFE_FREE(joined_map_str);
	// size_t	index = 0;
	// while (g_map[index])
	// {
	// 	DEBUGVS(g_map[index]);
	// 	index++;
	// }
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
	if (g_cubfile_data.floor_color == NOT_SET)
		exit_with_error_message(LACKING_ELEMENT, "F");
	if (g_cubfile_data.ceiling_color == NOT_SET)
		exit_with_error_message(LACKING_ELEMENT, "C");
}

void	get_line_data(t_data *data, char *cubfile_line, int fd)
{
	const char **element_items = (const char **)ft_split(cubfile_line, ' ');

	// 要は、他の要素が入りきっていないのに map だった場合。
	// つまり、初期化されていないデータが残っていないかを確認すれば良い。
	if (!all_elements_are_set() && is_map_line(cubfile_line))
		exit_with_error_message(SINGLE, "The map is in the wrong place.");
	if (ft_strcmp(element_items[0], "R") == 0)
		get_resolution(&element_items[1]);
	else if (ft_strcmp(element_items[0], "NO") == 0)
		set_texture(&g_cubfile_data.north_texture_path, &element_items[1], "NO");
	else if (ft_strcmp(element_items[0], "EA") == 0)
		set_texture(&g_cubfile_data.east_texture_path, &element_items[1], "EA");
	else if (ft_strcmp(element_items[0], "WE") == 0)
		set_texture(&g_cubfile_data.west_texture_path, &element_items[1], "WE");
	else if (ft_strcmp(element_items[0], "SO") == 0)
		set_texture(&g_cubfile_data.south_texture_path, &element_items[1], "SO");
	else if (ft_strcmp(element_items[0], "S") == 0)
		set_texture(&g_cubfile_data.sprite_texture_path, &element_items[1], "S");
	else if (ft_strcmp(element_items[0], "F") == 0)
		set_color(&g_cubfile_data.floor_color, &element_items[1], "F");
	else if (ft_strcmp(element_items[0], "C") == 0)
		set_color(&g_cubfile_data.ceiling_color, &element_items[1], "C");
	else if (is_map_line(cubfile_line))
	{
		exit_if_not_all_elements_are_set();
		create_map_array(data, cubfile_line, fd);
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



// TODO: そもそも、フリーする必要なくなったらこの関数要らない
void	exit_freeing_maps()
{
	// SAFE_FREE(g_map);
	// SAFE_FREE(g_map_to_check);
	exit_with_error_message("SINGLE", "The map is not surrounded by walls.\n");
}

bool	is_out_of_map(int x, int y)
{
	return (y < 0 || y >= g_cubfile_data.map_height || x < 0 || g_map[y][x] == '\0');
}

// TODO: strcpy 作成後、こちらを完成させてテスト
void	check_whether_map_is_surrounded(int current_x, int current_y)
{
	int	direction;
	int	new_x;
	int	new_y;

	g_map_to_check[current_y][current_x] = 'X';
	direction = 0;
	while (direction < 4)
	{
		new_x = current_x + dx[direction];
		new_y = current_y + dy[direction];
		if (is_out_of_map(new_x, new_y))
			exit_freeing_maps();
		// TODO: この関数はここから
		if (g_map_to_check[new_y][new_x] == )
	}
	char	current_c;

	if (current_y < 0 || current_y >= g_cubfile_data.map_height || current_x < 0 || g_map_to_check[current_y][current_x] == '\0')
		return ;
	current_c = g_map_to_check[current_y][current_x];
	if (current_c == '1')
		return ;
	if (!(img->w_map_c[row][col] == 'N' || img->w_map_c[row][col] == 'W'\
	|| img->w_map_c[row][col] == 'E' || img->w_map_c[row][col] == 'S' ||\
	img->w_map_c[row][col] == '0' || img->w_map_c[row][col] == '2'))
		return ;
	if (img->flag == 1)
		return ;
	if (row == 0 || col == 0 || row == i ||\
	col == (int)(ft_strlen(img->w_map_c[row]) - 1))
		img->flag = 1;
	if (up(img, row - 1, col) == 1 || down(img, row + 1, col) == 1 ||\
	right(img, row, col + 1) == 1 || right(img, row, col - 1) == 1)
		img->flag = 1;
	img->w_map_c[row][col] = 'x';
	fill(img, row + 1, col, i);
	fill(img, row - 1, col, i);
	fill(img, row, col + 1, i);
	fill(img, row, col - 1, i);
}

void	exit_if_map_is_not_surrounded_by_walls()
{
	g_cubfile_data.not_surrounded = false;
	check_whether_map_is_surrounded(g_player.x, g_player.y);
	if (g_cubfile_data.not_surrounded == true)
		exit_freeing_maps();
}

void	set_cubfile_data(t_data *data, char *filename)
{
	char		*line;
	const int	fd = open(filename, O_RDONLY);

	// map_init(data);
	// data->err_flag = false;
	if (fd == ERROR)
		exit_with_error_message(SINGLE, ".cub file cloud not be opened.\n");
	while (get_next_line(fd, &line) > 0)
	{
		// printf("%s\n", line);
		get_line_data(data, line, fd);
		if (g_map != NULL)		// if (get_line_data(data, line, fd) == ERROR)
			break ;
		// {
		// 	// なぜここで終わらせちゃわないのか？ free とか？
		// 	// data->err_flag = true;
		// 	// これはテスト用
		// 	return ;
		// }
		SAFE_FREE(line);
	}
	// SAFE_FREE(line);
	set_spawn_data_and_sprites_num(data);
	exit_if_map_is_not_surrounded_by_walls();
	// if (map_is_not_surrounded_by_walls())

	// TODO: sprite の malloc の必然性が分からない
	// なので後回し
	// data->sprite = malloc(sizeof(t_sprite) * data->sprite_num);
	// TODO: 同じく、sprite の位置の獲得の必然性もわからないので後で
	// get_sprites_positions(data);
	// check(data);
}

void	init_everything(char *filename)
{
	t_data	data;

	set_cubfile_data(&data, filename);
	// if (data.w_map[(int)data.player.p_y][(int)data.player.p_x + 1] == '1'\
	// || data.w_map[(int)data.player.p_y][(int)data.player.p_x - 1] == '1'\
	// || data.w_map[(int)data.player.p_y + 1][(int)data.player.p_x] == '1' ||\
	// data.w_map[(int)data.player.p_y - 1][(int)data.player.p_x] == '1')
	// {
	// 	free_reads(&data);
	// 	put_err_msg("player position\n");
	// 	exit(0);
	// }
	// init_elements(&data);
	// mlx_hook(data.win, 2, 1L << 0, key_pressed, &data);
	// mlx_hook(data.win, 3, 1L << 1, key_released, &data);
	// mlx_hook(data.win, 17, 1L << 17, finish_program, &data);
	// mlx_loop_hook(data.mlx, render_next_frame, &data);
	// mlx_loop(data.mlx);
	// TODO: close(fd);
}

int	main(int argc, char **argv)
{
	const char	*extension = ".cub";
	const char	*option = "--save";

	if (argc < 2)
		exit_with_error_message(SINGLE, "No arguments.\n");
	// TODO: SINGLE の場合、strerror の活用を考えると、改行は関数内に含めなくてはいけない
	if (argc > 3)
		exit_with_error_message(SINGLE, strerror(E2BIG));
	// TODO: 以下の２つはエラーパターンが同じなので、まとめる
	if (ft_strlen(argv[1]) < 5 || ft_strcmp(&argv[1][ft_strlen(argv[1]) - 4], extension) != 0)
		exit_with_error_message(SINGLE, strerror(EINVAL));
	if (argc > 2)
	{
		if (ft_strcmp(argv[2], option) != 0)
			exit_with_error_message(SINGLE, strerror(EINVAL));
		// TODO: save_picture(argv[1]);
	}
	else
		init_everything(argv[1]);
}

// int		get_line_data(t_data *data, char *cubfile_line, int fd)
// {
// 	const char **element_items = (const char **)ft_split(cubfile_line, ' ');

// 	if (ft_strcmp(element_items[0], "R") == 0)
// 		return (get_resolution(&element_items[1]));
// 	if (ft_strcmp(element_items[0], "NO") == 0)
// 		return (set_texture(&g_cubfile_data.north_texture_path, &element_items[1], "NO"));
// 	if (ft_strcmp(element_items[0], "EA") == 0)
// 		return (set_texture(&g_cubfile_data.east_texture_path, &element_items[1], "EA"));
// 	if (ft_strcmp(element_items[0], "WE") == 0)
// 		return (set_texture(&g_cubfile_data.west_texture_path, &element_items[1], "WE"));
// 	if (ft_strcmp(element_items[0], "SO") == 0)
// 		return (set_texture(&g_cubfile_data.south_texture_path, &element_items[1], "SO"));
// 	if (ft_strcmp(element_items[0], "S") == 0)
// 		return (set_texture(&g_cubfile_data.sprite_texture_path, &element_items[1], "S"));
// 	if (ft_strcmp(element_items[0], "F") == 0)
// 		return (set_color(&g_cubfile_data.floor_color, &element_items[1], "F"));
// 	if (ft_strcmp(element_items[0], "C") == 0)
// 		return (set_color(&g_cubfile_data.ceiling_color, &element_items[1], "C"));
// 	if (is_map_line(cubfile_line))
// 		return (create_map_array(data, cubfile_line, fd));
// 	// printf("%s\n", g_cubfile_data.north_texture_path);
// 	// printf("%s\n", g_cubfile_data.east_texture_path);
// 	// printf("%s\n", g_cubfile_data.west_texture_path);
// 	// printf("%s\n", g_cubfile_data.south_texture_path);
// 	// printf("%s\n", g_cubfile_data.sprite_texture_path);
// 	// printf("%d\n", g_cubfile_data.window_width);
// 	// printf("%d\n", g_cubfile_data.window_height);
// 	// printf("%d\n", g_cubfile_data.floor_color);
// 	// printf("%d\n", g_cubfile_data.ceiling_color);
// 	if (ft_strtrim(cubfile_line, " \t")[0] == '\0')
// 		return (SUCCESS);
// 	// こいつをなくす！！！！
// 	// return (ERROR);
// }