/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwaura <miwaura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 14:53:55 by miwaura           #+#    #+#             */
/*   Updated: 2020/09/16 15:23:41 by miwaura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_pressed(int keycode, t_data *p)
{
	t_data	*img;

	img = (t_data *)p;
	if (keycode == KEY_ESC)
		exit(0);
	else if (keycode == KEY_W && img->key.fd == 0)
		img->key.fd = 1;
	else if (keycode == KEY_S && img->key.bk == 0)
		img->key.bk = 1;
	else if (keycode == KEY_A && img->key.lt == 0)
		img->key.lt = 1;
	else if (keycode == KEY_D && img->key.rt == 0)
		img->key.rt = 1;
	else if (keycode == KEY_LEFT && img->key.rlt == 0)
		img->key.rlt = 1;
	else if (keycode == KEY_RIGHT && img->key.rrt == 0)
		img->key.rrt = 1;
	return (1);
}

int		key_released(int keycode, void *p)
{
	t_data	*img;

	img = (t_data *)p;
	if (keycode == KEY_W && img->key.fd == 1)
		img->key.fd = 0;
	else if (keycode == KEY_S && img->key.bk == 1)
		img->key.bk = 0;
	else if (keycode == KEY_A && img->key.lt == 1)
		img->key.lt = 0;
	else if (keycode == KEY_D && img->key.rt == 1)
		img->key.rt = 0;
	else if (keycode == KEY_LEFT && img->key.rlt == 1)
		img->key.rlt = 0;
	else if (keycode == KEY_RIGHT && img->key.rrt == 1)
		img->key.rrt = 0;
	return (1);
}
