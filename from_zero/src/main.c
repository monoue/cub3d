#include "../minilibx/mlx_beta/mlx.h"
#include "main.h"
#include "ft_printf/ft_printf.h"
#include "ft_printf/libft/libft.h"
#include "get_next_line/get_next_line.h"

int		exit_failure_with_err_msg(char *err_msg)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(err_msg, STDERR_FILENO);

	exit(EXIT_FAILURE);
	// 後で、全て void 型に変更
	return (1);
}

#include <string.h>

void	map_init(t_data *data)
{
	data->map.window_width = NOT_SET;
	data->map.window_height = NOT_SET;
	data->map.n_tex_path = NULL;
	data->map.s_tex_path = NULL;
	data->map.w_tex_path = NULL;
	data->map.e_tex_path = NULL;
	data->map.sprite_tex_path = NULL;
	data->map.floor_color = NOT_SET;
	data->map.elements_num = NOT_SET;
	data->map.ceiling_color = NOT_SET;
	data->err_flag = false;
}

void	exit_failure_closing_fd(char *err_msg, int fd)
{
	exit_failure_with_err_msg(err_msg);
	close(fd);
	exit(EXIT_FAILURE);
}

bool	is_valid_identifier(const char *first_word, const char *identifier)
{
	const size_t	fst_wrd_len = ft_strlen(first_word);
	const size_t	id_len = ft_strlen(identifier);

	return (ft_strncmp(first_word, identifier, MAX(fst_wrd_len, id_len)) == 0);
}

size_t	get_digits_num(const char *str)
{
	size_t	digits_num;

	digits_num = 0;
	while (ft_isdigit(str[digits_num]))
		digits_num++;
	return (digits_num);
}

int		get_resolution(t_map *map, void *mlx, const char **infos, size_t expected_infos_num)
{
	size_t			index;
	const size_t	info1_len = ft_strlen(infos[0]);
	size_t			info2_len;

	if (!(map->window_width == NOT_SET && map->window_height == NOT_SET))
		exit_failure_with_err_msg(".cub file has several \"R\" lines.");
	index = 0;
	while (infos[index] != NULL)
		index++;
	if (index != expected_infos_num)
		exit_failure_with_err_msg(".cub file: \"R\" line's informations' number is wrong.");
	info2_len = ft_strlen(infos[1]);
	if (!(info1_len == get_digits_num(infos[0]) || info2_len == get_digits_num(infos[1])))
		exit_failure_with_err_msg(".cub file: \"R\" line's information is invalid.");
	mlx_get_screen_size(mlx, &map->window_width, &map->window_height);
	map->window_width = MIN(map->window_width, ft_atoi(infos[0]));
	map->window_height = MIN(map->window_height, ft_atoi(infos[1]));
	// これも、void で済むかも
	ft_printf("%d\n", map->window_width);
	ft_printf("%d\n", map->window_height);
	return (SUCCESS);
}

int		get_cubfile_info(t_data *data, char *cubfile_line)
{
	const char **element_items = (const char **)ft_split(cubfile_line, ' ');

	if (is_valid_identifier(element_items[0], "R"))
		return (get_resolution(&data->map, data->mlx, &element_items[1], 2));
	if (is_valid_identifier(element_items[0], "NO"))
		return (get_texture_n(data, cubfile_line));
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

	map_init(data);
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
	// 	exit_failure_with_err_msg("map");
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
		return (exit_failure_with_err_msg("No arguments."));
	if (ft_strlen(argv[1]) < 5 || ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], extension, 4) != 0)
		return (exit_failure_with_err_msg("File's extension is not \".cub\".\n"));
	if (argc > 2)
	{
		if (ft_strlen(argv[2]) != ft_strlen(option) || ft_strncmp(argv[2], option, ft_strlen(option)) != 0)
			return (exit_failure_with_err_msg("Option is not \"--save\".\n"));
		// TODO: save_picture(argv[1]);
	}
	else
		init_everything(argv[1]);
}
