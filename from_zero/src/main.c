/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:49:30 by monoue            #+#    #+#             */
/*   Updated: 2020/10/29 10:15:27 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>

#include "check_map_error.h"
#include "create_maps.h"
#include "defs.h"
#include "error.h"
#include "init_mlx.h"
#include "libft/libft.h"
#include "main.h"
#include "../minilibx/mlx_beta/mlx.h"
#include "player.h"
#include "set_cubfile_data.h"

t_data g_data;

void	play_the_game(char *filename)
{
	set_cubfile_data(filename);

	// initialize_mlx_elements();
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
