#include "../minilibx/mlx_beta/mlx.h"
#include "main.h"
#include "ft_printf/ft_printf.h"
#include "ft_printf/libft/libft.h"
#include "get_next_line/get_next_line.h"

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

void	exit_failure_with_error_message(t_error_types message_type,  char *error_content)
// int		exit_failure_with_error_message(char *error_content)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	if (message_type == SINGLE)
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
	else if (message_type == INVALID_PATH)
	{
		ft_putstr_fd(".cub file: \"", STDERR_FILENO);
		ft_putstr_fd(error_content, STDERR_FILENO);
		ft_putstr_fd("\" line's path is invalid.\n", STDERR_FILENO);
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
		exit_failure_with_error_message(ID_OVERLAPPING, "R");
	if (ft_count_strs(infos) != 2)
		exit_failure_with_error_message(WRONG_INFO_NUM, "R");
	if (!ft_str_is_numeric(infos[0]) || !ft_str_is_numeric(infos[1]))
		exit_failure_with_error_message(INVALID_INFO, "R");
	mlx_get_screen_size(g_data.mlx, &g_cubfile_data.window_width, &g_cubfile_data.window_height);
	g_cubfile_data.window_width = MIN(g_cubfile_data.window_width, ft_atoi(infos[0]));
	g_cubfile_data.window_height = MIN(g_cubfile_data.window_height, ft_atoi(infos[1]));
	if (g_cubfile_data.window_width == 0 || g_cubfile_data.window_height == 0)
		exit_failure_with_error_message(INVALID_INFO, "R");
	// printf("%d, %d\n", g_cubfile_data.window_width, g_cubfile_data.window_height);
}

void	set_texture(char **texture_path, const char **infos, char *id)
{
	size_t			texture_i;

	if (*texture_path != NULL)
		exit_failure_with_error_message(ID_OVERLAPPING, id);
	if (ft_count_strs(infos) != 1)
		exit_failure_with_error_message(WRONG_INFO_NUM, id);
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
		exit_failure_with_error_message(INVALID_PATH, id);
	// printf("%s\n", g_cubfile_data.north_texture_path);
}

bool	is_out_of_color_range(int trgb_element)
{
	return (trgb_element < 0 || trgb_element > 255);
}

size_t	count_specific_c(char *str, char c)
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
		exit_failure_with_error_message(ID_OVERLAPPING, id);
	if (ft_count_strs(infos) != 1)
		exit_failure_with_error_message(WRONG_INFO_NUM, id);
	if (count_specific_c(infos[0], ',') != 2 || ft_count_strs(num_strs) != 3)
		exit_failure_with_error_message(INVALID_INFO, id);
	index = 0;
	while (index < 3)
	{
		if (!ft_str_is_numeric(num_strs[index]))
			exit_failure_with_error_message(INVALID_INFO, id);
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
			exit_failure_with_error_message(INVALID_INFO, id);
		rgb_index++;
	}
	*color = create_trgb(0, rgb_elements[0], rgb_elements[1], rgb_elements[2]);
}

bool	is_map_c(char c)
{
	return ((c >= '0' && c <= '2') || c == 'N' || c == 'E' || c == 'W' || c == 'S');
}

bool	is_map_line(char *cubfile_line)
{
	size_t	index;

	while (cubfile_line[index] != '\0')
	{
		if (is_map_c(cubfile_line[index]))
			return (true);
		index++;
	}
	return (false);
}


// TODO: 長さを予め指定すべきか、それとも行数を数えたの結果による malloc にすべきか決める
// char	g_map[MAX_MAP_LEN][MAX_MAP_LEN];
char	**g_map;

// TODO: 空行で一旦終了。それ以降にデータがある行があれば、"empty line" のエラーを吐かせる
// substr で行頭から切り取っていく？
// int		create_map_array(t_data *data, char *cubfile_line, int fd)
// {
// 	char	*map;
// 	char	*tmp;
// 	int		utils[3];

// 	map = ft_strdup("");
// 	tmp = map;
// 	utils[1] = 0;
// 	utils[2] = 0;
// 	while (get_next_line(fd, &cubfile_line) > 0)
// 	{
// 		if (cubfile_line[0] == '\0')
// 			error_map("invalid map\n", cubfile_line, map);
// 		map = get_map_in(cubfile_line, map, utils[1]);
// 		utils[1] = 1;
// 		if (utils[2]++ > 50 || ft_strlen(cubfile_line) > 50)
// 			error_map("large file\n", cubfile_line, map);
// 		free(cubfile_line);
// 	}
// 	map = get_map_in(cubfile_line, map, utils[1]);
// 	data->w_map = ft_split(map, '\n');
// 	data->w_map_c = ft_split(map, '\n');
// 	free(map);
// 	get_inf_sprite_num(data);
// 	free(cubfile_line);
// 	return (1);
// }

char	*ft_strjoin_with_n(char *map, char *line)
{
	char *tmp;

	tmp = map;
	map = ft_strjoin(map, "\n");
	if (!map)
		return (NULL);
	tmp = map;
	map = ft_strjoin(map, line);
	free(tmp);
	if (!map)
		return (NULL);
	return (map);
}

char	*get_map_in(char *line, char *map, int flag)
{
	char *tmp;

	tmp = NULL;
	if (line_check(line))
	{
		tmp = map;
		if (flag == 0)
			map = ft_strjoin(map, line);
		else
			map = ft_strjoin_with_n(map, line);
		if (!map)
		{
			free(tmp);
			return (NULL);
		}
		free(tmp);
	}
	(void)tmp;
	return (map);
}

void	create_map_array(t_data *data, char *cubfile_line, int fd)
{
	char	*map;
	char	*tmp;
	int		utils[3];
	size_t	row_count;

	map = ft_strdup("");
	tmp = map;
	utils[1] = 0;
	// utils[2] = 0;
	row_count = 0;
	while (get_next_line(fd, &cubfile_line) > 0)
	{
		if (cubfile_line[0] == '\0')
			error_map("invalid map\n", cubfile_line, map);
		map = get_map_in(cubfile_line, map, utils[1]);
		utils[1] = 1;
		if (row_count++ > 50 || ft_strlen(cubfile_line) > 50)
			error_map("large file\n", cubfile_line, map);
		free(cubfile_line);
	}
	map = get_map_in(cubfile_line, map, utils[1]);
	free(cubfile_line);
	data->w_map = ft_split(map, '\n');
	data->w_map_c = ft_split(map, '\n');
	free(map);
	get_inf_sprite_num(data);
}


// TODO: サブリナのを参考にしながら（でも間違っていたらしいので過信せず）、どうすればエラーにならないか、思考錯誤！！！
bool	g_map_up = false;

void	get_line_data(t_data *data, char *cubfile_line, int fd)
{
	const char **element_items = (const char **)ft_split(cubfile_line, ' ');

	if (g_map_up == false && is_map_line(cubfile_line))
		exit_failure_with_error_message(SINGLE, "The map is in the wrong place.");
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
		create_map_array(data, cubfile_line, fd);
	g_map_up = true;
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

void	set_cubfile_data(t_data *data, char *filename)
{
	char		*line;
	const int	fd = open(filename, O_RDONLY);

	// map_init(data);
	// data->err_flag = false;
	if (fd == ERROR)
		exit_failure_with_error_message(SINGLE, ".cub file cloud not be opened.\n");
	while (get_next_line(fd, &line) > 0)
	{
		// printf("%s\n", line);
		get_line_data(data, line, fd);
		// if (get_line_data(data, line, fd) == ERROR)
		// {
		// 	// なぜここで終わらせちゃわないのか？ free とか？
		// 	// data->err_flag = true;
		// 	// これはテスト用
		// 	return ;
		// }
		SAFE_FREE(line);
	}
	SAFE_FREE(line);
	// map_elements_check(data);
	// data->sprite = malloc(sizeof(t_sprite) * data->sprite_num);
	// if (data->err_flag == true)
	// {
	// 	free_reads(data);
	// 	exit_failure_with_error_message("map");
	// 	exit(0);
	// }
	// get_inf_sprite_pos(data);
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
		exit_failure_with_error_message(SINGLE, "No arguments.\n");
	if (ft_strlen(argv[1]) < 5 || ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], extension, 4) != 0)
		exit_failure_with_error_message(SINGLE, "File's extension is not \".cub\".\n");
	if (argc > 2)
	{
		if (ft_strlen(argv[2]) != ft_strlen(option) || ft_strncmp(argv[2], option, ft_strlen(option)) != 0)
			exit_failure_with_error_message(SINGLE, "Option is not \"--save\".\n");
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