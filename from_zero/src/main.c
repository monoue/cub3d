#include "main.h"
#include "ft_printf/ft_printf.h"
#include "ft_printf/libft/libft.h"
#include "get_next_line/get_next_line.h"

int		put_err_msg(char *err_msg)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(err_msg, STDERR_FILENO);
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

	// こいつはあるかも
	data->err_flag = false;
}

void	exit_failure_closing_fd(char *err_msg, int fd)
{
	put_err_msg(err_msg);
	close(fd);
	exit(EXIT_FAILURE);
}

int		get_resolution(t_data *data, char *resolution_line)
{
	size_t			index;
	const size_t	line_len = ft_strlen(resolution_line);

	mlx_get_screen_size(data->mlx, &data->map.window_width, &data->map.window_height);
	data->map.elements_num++;
	index = 0;
	while (index < line_len && resolution_line[index] == ' ')
		index++;
	if (index < line_len)
		data->map.window_width = MIN(data->map.window_width, ft_atoi(&resolution_line[index]));
	while (index < line_len && ft_isdigit(resolution_line[index]))
		index++;
	while (index < line_len && resolution_line[index] == ' ')
		index++;
	if (index < line_len)
		data->map.window_height = MIN(data->map.window_height, ft_atoi(&resolution_line[index]));
	while (index < line_len && ft_isdigit(resolution_line[index]))
		index++;
	if (index != line_len)
		return (ERROR);
	return (SUCCESS);
}

bool	is_valid_cubfile_line(const char *cubfile_line, const char *identifier, const int info_num)
{
	const char		*array = ft_split(cubfile_line, ' ');
	const char		first_word = array[0];
	const size_t	fst_wrd_len = ft_strlen(first_word);
	const size_t	id_len = ft_strlen(identifier);
	int				word_count;

	word_count = 0;
	while (array[word_count] != NULL)
		word_count++;
	if (word_count - 1 != info_num)
		return (false);
	return (ft_strncmp(first_word, identifier, MAX(fst_wrd_len, id_len)) == 0);
}

int		get_cubfile_info(t_data *data, char *cubfile_line)
{
	if (is_valid_cubfile_line(cubfile_line, "R", 2))
	// ここまで
		return (get_resolution(data, &cubfile_line[1])); // こういう風にできるかな？？
	else if (is_valid_cubfile_line(cubfile_line, "NO", 1))
		return (get_texture_n(data, cubfile_line));
	else if (is_valid_cubfile_line(cubfile_line, "SO", 1))
		return (get_texture_s(data, cubfile_line));
	else if (is_valid_cubfile_line(cubfile_line, "WE", 1))
		return (get_texture_w(data, cubfile_line));
	else if (is_valid_cubfile_line(cubfile_line, "EA", 1))
		return (get_texture_e(data, cubfile_line));
	else if (is_valid_cubfile_line(cubfile_line, "S", 1))
		return (get_sprite(data, cubfile_line));
	else if (is_valid_cubfile_line(cubfile_line, "F", 1))
		return (get_colors(data, cubfile_line, 'F'));
	else if (is_valid_cubfile_line(cubfile_line, "C", 1))
		return (get_colors(data, cubfile_line, 'C'));
	else if (mapline(cubfile_line) == 0)
		return (get_map(data, cubfile_line));
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
			// なぜここで終わらせちゃわないのか？ free とか？
			data->err_flag = true;
		SAFE_FREE(line);
	}
	SAFE_FREE(line);
	map_elements_check(data);
	data->sprite = malloc(sizeof(t_sprite) * data->sprite_num);
	if (data->err_flag == true)
	{
		free_reads(data);
		put_err_msg("map");
		exit(0);
	}
	get_inf_sprite_pos(data);
	check(data);
}

void	init_game(char *filename)
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
		return (put_err_msg("At least one argument needed.\n"));
	if (ft_strlen(argv[1]) < 5 || ft_strncmp(&argv[1][ft_strlen(argv[1]) - 4], extension, 4) != 0)
		return (put_err_msg(".cub file must be specified.\n"));
	if (argc > 2)
	{
		if (ft_strlen(argv[2]) != ft_strlen(option) || ft_strncmp(argv[2], option, ft_strlen(option)) != 0)
			return (put_err_msg("Invalid option. Option: --save\n"));
		// TODO: save_picture(argv[1]);
	}
	else
		init_everthing(argv[1]);
}
