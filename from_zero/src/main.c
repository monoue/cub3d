#include "../minilibx/mlx_beta/mlx.h"
#include "main.h"
#include "ft_printf/ft_printf.h"
#include "ft_printf/libft/libft.h"
#include "get_next_line/get_next_line.h"
// こんな感じ？
const char *g_texture_file_names[TEXTURES_NUM] =
{
	BLUESTONE_XPM,
	BARREL_XPM,
	COLORSTONE_XPM,
	GREYSTONE_XPM,
	REDBRICK_XPM
};
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

int		exit_failure_with_error_message(t_error_types message_type, char *error_content)
// int		exit_failure_with_error_message(char *error_content)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	if (message_type == SINGLE)
		ft_putstr_fd(error_content, STDERR_FILENO);
	else if (message_type == ID_OVERLAPPING)
	{
		ft_putstr_fd(".cub file has more than one \"", STDERR_FILENO);
		ft_putstr_fd(error_content, STDERR_FILENO);
		ft_putstr_fd("\" lines.", STDERR_FILENO);
	}
	else if (message_type == WRONG_INFO_NUM)
	{
		ft_putstr_fd(".cub file: \"", STDERR_FILENO);
		ft_putstr_fd(error_content, STDERR_FILENO);
		ft_putstr_fd("\" line's informations' number is wrong.", STDERR_FILENO);
	}
	else if (message_type == INVALID_INFO)
	{
		ft_putstr_fd(".cub file: \"", STDERR_FILENO);
		ft_putstr_fd(error_content, STDERR_FILENO);
		ft_putstr_fd("\" line's informations is invalid.", STDERR_FILENO);
	}
	else if (message_type == INVALID_PATH)
	{
		ft_putstr_fd(".cub file: \"", STDERR_FILENO);
		ft_putstr_fd(error_content, STDERR_FILENO);
		ft_putstr_fd("\" line's path is invalid.", STDERR_FILENO);
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
	exit_failure_with_error_message(SINGLE, error_content);
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

// TODO: ゼロもしくはそれ以下だった時の処理！！
int		get_resolution(const char **infos)
{
	size_t			info_num;
	const size_t	info1_len = ft_strlen(infos[0]);
	size_t			info2_len;

	if (!(g_map.window_width == NOT_SET && g_map.window_height == NOT_SET))
		exit_failure_with_error_message(ID_OVERLAPPING, "R");
	info_num = 0;
	while (infos[info_num] != NULL)
		info_num++;
	if (info_num != 2)
		exit_failure_with_error_message(WRONG_INFO_NUM, "R");
	info2_len = ft_strlen(infos[1]);
	if (!(info1_len == get_digits_num(infos[0]) || info2_len == get_digits_num(infos[1])))
		exit_failure_with_error_message(INVALID_INFO, "R");
	mlx_get_screen_size(g_data.mlx, &g_map.window_width, &g_map.window_height);
	g_map.window_width = MIN(g_map.window_width, ft_atoi(infos[0]));
	g_map.window_height = MIN(g_map.window_height, ft_atoi(infos[1]));
	// printf("%d, %d\n", g_map.window_width, g_map.window_height);
	return (SUCCESS);
}

int		set_texture(char **texture_path, const char **infos, char *id)
{
	size_t			info_num;
	size_t			texture_i;

	if (*texture_path != NULL)
		exit_failure_with_error_message(ID_OVERLAPPING, id);
	info_num = 0;
	while (infos[info_num] != NULL)
		info_num++;
	if (info_num != 1)
		exit_failure_with_error_message(WRONG_INFO_NUM, id);
	texture_i = 0;
	// printf("%s\n", g_texture_file_names[GREYSTONE]);
	// printf("%s\n", infos[0]);
	while (texture_i < TEXTURES_NUM)
	{
		if (ft_strcmp(g_texture_file_names[texture_i], infos[0]) == 0)
		{
			if (ft_strcmp(id, "NO") == 0)
				g_map.north_texture_path = ft_strdup(infos[0]);
			else if (ft_strcmp(id, "EA") == 0)
				g_map.east_texture_path = ft_strdup(infos[0]);
			else if (ft_strcmp(id, "WE") == 0)
				g_map.west_texture_path = ft_strdup(infos[0]);
			else if (ft_strcmp(id, "SO") == 0)
				g_map.south_texture_path = ft_strdup(infos[0]);
			break ;
		}
		texture_i++;
	}
	if (texture_i == TEXTURES_NUM)
		exit_failure_with_error_message(INVALID_PATH, id);
	// printf("%s\n", g_map.north_texture_path);
	return (SUCCESS);
}

// int		get_colors_num(char *line, int i, int *sum)
// {
// 	int j;

// 	j = 0;
// 	while (j < 3)
// 	{
// 		if (line[i] == ',')
// 			i++;
// 		while (ft_isdigit(line[i]))
// 		{
// 			sum[j] = sum[j] * 10 + (line[i] - 48);
// 			if (sum[j] > 255)
// 				return (0);
// 			i++;
// 		}
// 		j++;
// 	}
// 	return (1);
// }

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

// グローバルだから第一引数要らない。
// 色の計算のメカニズムを、例のサイトを参考に確認する。
// int		set_color(char *cubfile_line, char id)
// {

// 	int i;
// 	int sum[3];

// 	i = 0;
// 	// 初期化してる(多分不要)
// 	while (i < 3)
// 	{
// 		sum[i] = 0;
// 		i++;
// 	}
// 	// ここまで

// 	// 行の何文字目かのインデックス
// 	i = 2;
// 	while (cubfile_line[i] == ' ')
// 		i++;
// 	if (get_colors_num(&cubfile_line[i], sum) == 0)
// 		return (0);
// 	if (id == 'F')
// 		img->map.floor_color = sum[0] * 65536 + sum[1] * 256 + sum[2];
// 	if (id == 'C')
// 		img->map.ceiling_color = sum[0] * 65536 + sum[1] * 256 + sum[2];
// 	img->map.elements_num++;
// 	return (SUCCESS);
// }

int		set_color(int *color, char *infos, char *id)
{
	size_t	info_num;
	char	**rgb_colors;

	if (*color != NOT_SET)
		exit_failure_with_error_message(ID_OVERLAPPING, id);
	info_num = 0;
	while (infos[info_num] != NULL)
		info_num++;
	if (info_num != 1)
		exit_failure_with_error_message(WRONG_INFO_NUM, id);
	// texture_i = 0;
	// printf("%s\n", g_texture_file_names[GREYSTONE]);
	// printf("%s\n", infos[0]);


	// // 行の何文字目かのインデックス
	// i = 2;
	// while (cubfile_line[i] == ' ')
	// 	i++;
	// if (get_colors_num(&cubfile_line[i], sum) == 0)
	// 	return (0);
	// if (id == 'F')
	// 	img->map.floor_color = sum[0] * 65536 + sum[1] * 256 + sum[2];
	// if (id == 'C')
	// 	img->map.ceiling_color = sum[0] * 65536 + sum[1] * 256 + sum[2];
	// img->map.elements_num++;
	return (SUCCESS);
}

int		get_cubfile_info(t_data *data, char *cubfile_line)
{
	const char **element_items = (const char **)ft_split(cubfile_line, ' ');

	if (is_valid_identifier(element_items[0], "R"))
		return (get_resolution(&element_items[1]));
	if (is_valid_identifier(element_items[0], "NO"))
		return (set_texture(&g_map.north_texture_path, &element_items[1], "NO"));
	if (is_valid_identifier(element_items[0], "EA"))
		return (set_texture(&g_map.east_texture_path, &element_items[1], "EA"));
	if (is_valid_identifier(element_items[0], "WE"))
		return (set_texture(&g_map.west_texture_path, &element_items[1], "WE"));
	if (is_valid_identifier(element_items[0], "SO"))
		return (set_texture(&g_map.south_texture_path, &element_items[1], "SO"));
	if (is_valid_identifier(element_items[0], "S"))
		return (set_texture(&g_map.sprite_texture_path, &element_items[1], "S"));
	if (is_valid_identifier(element_items[0], "F"))
		return (set_color(&g_map.floor_color, &element_items[1], "F"));
	if (is_valid_identifier(element_items[0], "C"))
		return (set_color(&g_map.ceiling_color, &element_items[1], "C"));
	// if (is_valid_identifier(cubfile_line, "F"))
	// 	return (set_color(&g_map.floor_color, 'F'));
	// if (is_valid_identifier(cubfile_line, "C"))
	// 	return (set_color(&g_map.ceiling_color, 'C'));
	if (ft_strtrim(cubfile_line, " \t")[0] == '\0')
		return (SUCCESS);
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
		// printf("%s\n", line);
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
