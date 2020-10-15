/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 15:17:32 by miwaura           #+#    #+#             */
/*   Updated: 2020/10/15 10:36:55 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_data *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		render_next_frame(void *p)
{
	t_data	*img;
	int		x;

	img = (t_data *)p;
	x = 0;
	zbuffer_init(img);
	ray_cast(img, x);
	sprite_init(img);
	sort_sprite(img);
	x = 0;
	sprites(img, x);
	moves(img);
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	free(img->zbuffer);
	return (0);
}

void	init_elements(t_data *img)
{
	img->mlx = mlx_init();
	img->img = mlx_new_image(img->mlx, img->map.window_width, img->map.window_height);
	img->addr = mlx_get_data_addr(img->img,\
	&img->bits_per_pixel, &img->line_length, &img->endian);
	img->win = mlx_new_window(img->mlx,\
	img->map.window_width, img->map.window_height, "Hello");
	player(img);
	key(img);
	set_textures(img);
}

void	init_game(char *file)
{
	t_data img;

	read_map_open(&img, file);
	if (img.w_map[(int)img.player.p_y][(int)img.player.p_x + 1] == '1'\
	|| img.w_map[(int)img.player.p_y][(int)img.player.p_x - 1] == '1'\
	|| img.w_map[(int)img.player.p_y + 1][(int)img.player.p_x] == '1' ||\
	img.w_map[(int)img.player.p_y - 1][(int)img.player.p_x] == '1')
	{
		free_reads(&img);
		exit_failure_with_err_msg("player position\n");
		exit(0);
	}
	init_elements(&img);
	mlx_hook(img.win, 2, 1L << 0, key_pressed, &img);
	mlx_hook(img.win, 3, 1L << 1, key_released, &img);
	mlx_hook(img.win, 17, 1L << 17, finish_program, &img);
	mlx_loop_hook(img.mlx, render_next_frame, &img);
	mlx_loop(img.mlx);
}

int		main(int argc, char **argv)
{
	if (argc < 2 || 3 < argc)
		return (exit_failure_with_err_msg("Invalid arguments.\n"));
	if (!ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
		return (exit_failure_with_err_msg(".cub file must be specified.\n"));
	if (argc == 3 && ft_strncmp(argv[2], "--save", ft_strlen(argv[2])) != 0)
		return (exit_failure_with_err_msg("Invalid option. Options: --save\n"));
	if (argc == 2)
		init_game(argv[1]);
	else
		save_picture(argv[1]);
	return (0);
}
