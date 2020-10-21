#include "../minilibx/mlx_beta/mlx.h"
#include "main.h"
#include "ft_printf/ft_printf.h"
#include "ft_printf/libft/libft.h"
#include "get_next_line/get_next_line.h"
// こんな感じ？
int		exit_failure_with_error_message(size_t message_type, char *error_content)
// int		exit_failure_with_error_message(char *error_content)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	if (message_type == SINGLE)
		ft_putstr_fd(error_content, STDERR_FILENO);
	else if (message_type == ID_OVERLAPPING)
	{
		ft_putstr_fd(".cub file has more than one ", STDERR_FILENO);
		ft_putstr_fd(error_content, STDERR_FILENO);
		ft_putstr_fd(" lines.", STDERR_FILENO);
	}
	else if (message_type == WRONG_INFO_NUM)
	{
		ft_putstr_fd(".cub file: ", STDERR_FILENO);
		ft_putstr_fd(error_content, STDERR_FILENO);
		ft_putstr_fd(" line's informations' number is wrong.", STDERR_FILENO);
	}
	exit(EXIT_FAILURE);
	// 後で、全て void 型に変更
	return (1);
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

t_map g_map =
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

void	exit_failure_closing_fd(char *error_content, int fd)
{
	exit_failure_with_error_message(error_content);
	close(fd);
	exit(EXIT_FAILURE);
}

bool	is_valid_identifier(const char *first_word, const char *identifier)
{
	const size_t	fst_wrd_len = ft_strlen(first_word);
	const size_t	id_len = ft_strlen(identifier);

	return (ft_strcmp(first_word, identifier) == 0);
}

size_t	get_digits_num(const char *str)
{
	size_t	digits_num;

	digits_num = 0;
	while (ft_isdigit(str[digits_num]))
		digits_num++;
	return (digits_num);
}

int		get_resolution(const char **infos)
{
	size_t			index;
	const size_t	info1_len = ft_strlen(infos[0]);
	size_t			info2_len;

	if (!(g_map.window_width == NOT_SET && g_map.window_height == NOT_SET))
		exit_failure_with_error_message(ID_OVERLAPPING, "R");
	index = 0;
	while (infos[index] != NULL)
		index++;
	if (index != 2)
		exit_failure_with_error_message(WRONG_INFO_NUM, ".cub file: \"R\" line's informations' number is wrong.");
	info2_len = ft_strlen(infos[1]);
	if (!(info1_len == get_digits_num(infos[0]) || info2_len == get_digits_num(infos[1])))
		exit_failure_with_error_message(SINGLE, ".cub file: \"R\" line's information is invalid.");
	mlx_get_screen_size(g_data.mlx, &g_map.window_width, &g_map.window_height);
	g_map.window_width = MIN(g_map.window_width, ft_atoi(infos[0]));
	g_map.window_height = MIN(g_map.window_height, ft_atoi(infos[1]));
	printf("%d, %d\n", g_map.window_width, g_map.window_height);
	return (SUCCESS);
}

// int		get_resolution(t_map *map, void *mlx, const char **infos, size_t expected_infos_num)
// {
// 	size_t			index;
// 	const size_t	info1_len = ft_strlen(infos[0]);
// 	size_t			info2_len;

// 	if (!(map->window_width == NOT_SET && map->window_height == NOT_SET))
// 		exit_failure_with_error_message(".cub file has several \"R\" lines.");
// 	index = 0;
// 	while (infos[index] != NULL)
// 		index++;
// 	if (index != expected_infos_num)
// 		exit_failure_with_error_message(".cub file: \"R\" line's informations' number is wrong.");
// 	info2_len = ft_strlen(infos[1]);
// 	if (!(info1_len == get_digits_num(infos[0]) || info2_len == get_digits_num(infos[1])))
// 		exit_failure_with_error_message(".cub file: \"R\" line's information is invalid.");
// 	mlx_get_screen_size(mlx, &map->window_width, &map->window_height);
// 	map->window_width = MIN(map->window_width, ft_atoi(infos[0]));
// 	map->window_height = MIN(map->window_height, ft_atoi(infos[1]));
// 	return (SUCCESS);
// }

// TODO: ここから
void	n_texture_set(t_data *img, char *ptr, char *path)
{
	ptr = img->map.north_texture_path;
	img->map.north_texture_path = ft_strdup(path);
	free(ptr);
}

int		case_n(t_data *img, char *line, int i, char *ptr)
{
	if (ft_strncmp(line + i, "./images/redbrick.xpm", 23) == 0)
	{
		n_texture_set(img, ptr, "./images/redbrick.xpm");
		return (1);
	}
	if (ft_strncmp(line + i, "./images/greystone.xpm", 24) == 0)
	{
		n_texture_set(img, ptr, "./images/greystone.xpm");
		return (1);
	}
	return (0);
}

int		get_texture_n(t_data *img, char *line)
{
	int		i;
	char	*ptr;

	i = 3;
	ptr = NULL;
	while (line[i] == ' ')
		i++;
	if (case_n(img, line, i, ptr) == 1)
		return (1);
	if (ft_strncmp(line + i, "./images/bluestone.xpm", 24) == 0)
	{
		n_texture_set(img, ptr, "./images/bluestone.xpm");
		return (1);
	}
	if (ft_strncmp(line + i, "./images/colorstone.xpm", 25) == 0)
	{
		n_texture_set(img, ptr, "./images/colorstone.xpm");
		return (1);
	}
	return (0);
}

// TODO: ここから
int		set_texture(char **texture_path, const char **infos, char *direction_identifier)
{
	size_t			index;
	// const size_t	info1_len = ft_strlen(infos[0]);
	// size_t			info2_len;

	if (*texture_path != NULL)
		exit_failure_with_error_message(ID_OVERLAPPING, direction_identifier);
	index = 0;
	while (infos[index] != NULL)
		index++;
	if (index != 1)
		exit_failure_with_error_message(".cub file: \"R\" line's informations' number is wrong.");
	info2_len = ft_strlen(infos[1]);
	if (!(info1_len == get_digits_num(infos[0]) || info2_len == get_digits_num(infos[1])))
		exit_failure_with_error_message(".cub file: \"R\" line's information is invalid.");
	mlx_get_screen_size(g_data.mlx, &g_map.window_width, &g_map.window_height);
	g_map.window_width = MIN(g_map.window_width, ft_atoi(infos[0]));
	g_map.window_height = MIN(g_map.window_height, ft_atoi(infos[1]));
	printf("%d, %d\n", g_map.window_width, g_map.window_height);
	return (SUCCESS);

}

int		get_cubfile_info(t_data *data, char *cubfile_line)
{
	const char **element_items = (const char **)ft_split(cubfile_line, ' ');

	// if (is_valid_identifier(element_items[0], "R"))
	// 	return (get_resolution(&data->map, data->mlx, &element_items[1], 2));
	// if (is_valid_identifier(element_items[0], "NO"))
	// 	return (set_texture(&data->map.north_texture_path, &element_items[1]));
	if (is_valid_identifier(element_items[0], "R"))
		return (get_resolution(&element_items[1]));
	if (is_valid_identifier(element_items[0], "NO"))
		// return (set_texture(g_map.north_texture_path, &element_items[1]));
		return (set_texture(&g_map.north_texture_path, &element_items[1], "NO"));
	// else if (is_valid_identifier(cubfile_line, "SO", 1))
	// 	return (get_texture_s(data, cubfile_line));
	// else if (is_valid_identifier(cubfile_line, "WE", 1))
	// 	return (get_texture_w(data, cubfile_line));
	// else if (is_valid_identifier(cubfile_line, "EA", 1))
	// 	return (get_texture_e(data, cubfile_line));
	// else if (is_valid_identifier(cubfile_line, "S", 1))
	// 	return (get_sprite(data, cubfile_line));
	// else if (is_valid_identifier(cubfile_line, "F", 1))
	// 	return (get_colors(data, cubfile_line, 'F'));
	// else if (is_valid_identifier(cubfile_line, "C", 1))
	// 	return (get_colors(data, cubfile_line, 'C'));
	// else if (mapline(cubfile_line) == 0)
	// 	return (get_map(data, cubfile_line));
	return (ERROR);
}

void	read_map_open(t_data *data, char *filename)
{
	char	*line;

	// map_init(data);
	data->err_flag = false;
	if ((data->fd = open(filename, O_RDONLY)) == ERROR)
		exit_failure_closing_fd("open file", data->fd);
	while (get_next_line(data->fd, &line) > 0)
	{
		if (get_cubfile_info(data, line) == ERROR)
		{
			// なぜここで終わらせちゃわないのか？ free とか？
			// data->err_flag = true;
			// これはテスト用
			return ;
		}
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

	read_map_open(&data, filename);
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
}

int	main(int argc, char **argv)
{
	const char	*extension = ".cub";
	const char	*option = "--save";

	if (argc < 2)
		return (exit_failure_with_error_message(SINGLE, "No arguments."));
	if (ft_strlen(argv[1]) < 5 || ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], extension, 4) != 0)
		return (exit_failure_with_error_message(SINGLE, "File's extension is not \".cub\".\n"));
	if (argc > 2)
	{
		if (ft_strlen(argv[2]) != ft_strlen(option) || ft_strncmp(argv[2], option, ft_strlen(option)) != 0)
			return (exit_failure_with_error_message(SINGLE, "Option is not \"--save\".\n"));
		// TODO: save_picture(argv[1]);
	}
	else
		init_everything(argv[1]);
}
