/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_walls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 14:44:05 by miwaura           #+#    #+#             */
/*   Updated: 2020/10/14 13:38:47 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cal_hit_wall(t_data *img)
{
	if (img->ray.sd_di_x < img->ray.sd_di_y)
	{
		img->ray.sd_di_x += img->ray.dl_di_x;
		img->ray.mp_x += img->ray.st_x;
		if (img->ray.st_x == 1)
		{
			img->ray.side = WALL_N;
		}
		else if (img->ray.st_x == -1)
		{
			img->ray.side = WALL_S;
		}
	}
	else
	{
		img->ray.sd_di_y += img->ray.dl_di_y;
		img->ray.mp_y += img->ray.st_y;
		if (img->ray.st_y == 1)
		{
			img->ray.side = WALL_W;
		}
		else if (img->ray.st_y == -1)
			img->ray.side = WALL_E;
	}
}

void	cal_hit(t_data *img)
{
	while (img->ray.hit == 0)
	{
		cal_hit_wall(img);
		if (img->w_map[img->ray.mp_y][img->ray.mp_x] == '1')
			img->ray.hit = 1;
	}
	if (img->ray.side == 0 || img->ray.side == 1)
	{
		img->ray.p_w_di = (img->ray.mp_x - img->player.p_x +\
		(1 - img->ray.st_x) / 2) / img->ray.ray_dir_x;
	}
	else
	{
		img->ray.p_w_di = (img->ray.mp_y - img->player.p_y +\
		(1 - img->ray.st_y) / 2) / img->ray.ray_dir_y;
	}
}

void	cal_collision(t_data *img)
{
	if (img->ray.ray_dir_x < 0)
	{
		img->ray.st_x = -1;
		img->ray.sd_di_x = (img->player.p_x - img->ray.mp_x) * img->ray.dl_di_x;
	}
	else
	{
		img->ray.st_x = 1;
		img->ray.sd_di_x = (img->ray.mp_x + 1.0 - img->player.p_x)\
		* img->ray.dl_di_x;
	}
	if (img->ray.ray_dir_y < 0)
	{
		img->ray.st_y = -1;
		img->ray.sd_di_y = (img->player.p_y - img->ray.mp_y)\
		* img->ray.dl_di_y;
	}
	else
	{
		img->ray.st_y = 1;
		img->ray.sd_di_y = (img->ray.mp_y + 1.0 - img->player.p_y)\
		* img->ray.dl_di_y;
	}
	cal_hit(img);
}

void	ray_cast(t_data *img, int x)
{
	x = 0;
	while (x < img->map.window_width)
	{
		ray_init(x, img->map.window_width, img);
		cal_collision(img);
		texture_cal(img, x);
		x++;
	}
}
