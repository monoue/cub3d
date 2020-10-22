/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 10:41:49 by sperrin           #+#    #+#             */
/*   Updated: 2020/10/16 11:46:54 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		expose_hook(t_env *e)
{
	if (e->screenshot == 0)
		mlx_put_image_to_window(e->mlx, e->screen.win, e->img, 0, 0);
	return (0);
}

int		loop_hook(t_env *e)
{
	(void)e;
	draw_wolf(e);
	return (0);
}

int		ft_init(char *cub, int bmp)
{
	t_env	e;

	init_player(&e);
	e.mlx = mlx_init();
	e.screenshot = 0;
	read_file(&e, cub);
	e.img = mlx_new_image(e.mlx, e.screen.width, e.screen.height);
	e.edit = (int *)mlx_get_data_addr(e.img, &(e.bpx), &(e.szl), &(e.endiant));
	if (bmp == 1)
		make_screenshot(&e);
	e.screen.win = mlx_new_window(e.mlx, e.screen.width,
	e.screen.height, "cub3d");
	e.h = -100;
	e.w = -100;
	mlx_hook(e.screen.win, KEYPRESS, KEYPRESSMASK, key_press, &e);
	mlx_hook(e.screen.win, KEYRELEASE, KEYRELEASEMASK, key_release, &e);
	mlx_hook(e.screen.win, 17, 0, destroy_img, &e);
	mlx_expose_hook(e.screen.win, expose_hook, &e);
	mlx_loop_hook(e.mlx, loop_hook, &e);
	mlx_loop(e.mlx);
	return (1);
}

int		main(int ac, char **av)
{
	if (ac == 3 && ft_namecheck(av[1], "cub") && ft_savecheck(av[2], "--save"))
		ft_init(av[1], 1);
	else if (ac == 2 && ft_namecheck(av[1], "cub"))
		ft_init(av[1], 0);
	else
		write(2, "ERROR\n INVALIDE ARGUMENTS DUDE\n", 32);
	return (0);
}
