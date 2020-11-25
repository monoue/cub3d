/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:49:30 by monoue            #+#    #+#             */
/*   Updated: 2020/11/25 09:26:13 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
// #include <stdio.h>

#include "src/defs.h"
#include "src/error_exit/error_exit.h"
#include "init_mlx.h"
#include "src/libft/libft.h"
#include "src/set_cubfile_data/set_cubfile_data.h"
#include "src/game_loop/event_hook.h"

static void	set_textures(void)
{
	size_t		t_i;

	t_i = 0;
	while (t_i < TEXTURES_NUM)
	{
		g_textures[t_i].img_ptr = mlx_xpm_file_to_image(
			g_mlx.mlx_ptr,
			g_textures[t_i].path,
			&g_textures[t_i].width,
			&g_textures[t_i].height);
		if (g_textures[t_i].img_ptr == NULL)
			exit_with_error_message(ERRNO, NULL);
		g_textures[t_i].addr = mlx_get_data_addr(
			g_textures[t_i].img_ptr,
			&g_textures[t_i].bits_per_pixel,
			&g_textures[t_i].line_length,
			&g_textures[t_i].endian);
		t_i++;
	}
}

static void	init_mlx(void)
{
	g_mlx.mlx_ptr = mlx_init();
	g_mlx.win_ptr = mlx_new_window(g_mlx.mlx_ptr, g_cubfile_data.window_width,
								g_cubfile_data.window_height, "Monoue's cub3D");
								// TODO: defs にメッセージ入れる
	g_img.img_ptr = mlx_new_image(g_mlx.mlx_ptr, g_cubfile_data.window_width,
												g_cubfile_data.window_height);
	g_img.addr = mlx_get_data_addr(g_img.img_ptr, &g_img.bits_per_pixel,
											&g_img.line_length, &g_img.endian);
	set_textures();
}

static void	play_the_game(char *filename)
{
	set_cubfile_data(filename);
	init_mlx();
	event_hook();
	mlx_loop_hook(g_mlx.mlx_ptr, &game_loop, NULL);
	mlx_loop(g_mlx.mlx_ptr);
}

int	main(int argc, char **argv)
{
	const char	*extension = ".cub";
	const char	*option = "--save";

	if (argc < 2)
		exit_with_error_message(SINGLE, "No arguments");
	if (argc > 3)
		exit_with_error_message(SINGLE, strerror(E2BIG));
	// TODO: 以下の２つはエラーパターンが同じなので、まとめる
	if (ft_strlen(argv[1]) < 5 || ft_strcmp(&argv[1][ft_strlen(argv[1]) - 4], extension) != 0)
		exit_with_error_message(SINGLE, strerror(EINVAL));
	if (argc == 2)
		play_the_game(argv[1]);
	else
	{
		if (ft_strcmp(argv[2], option) != 0)
			exit_with_error_message(SINGLE, strerror(EINVAL));
		// TODO: save_picture(argv[1]);
	}
}
