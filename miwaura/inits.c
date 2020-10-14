/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 14:51:13 by miwaura           #+#    #+#             */
/*   Updated: 2020/10/14 13:38:47 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sprite_init(t_data *img)
{
	img->sprite_cal.sprite_x = 0;
	img->sprite_cal.sprite_y = 0;
	img->sprite_cal.invdet = 0;
	img->sprite_cal.trans_x = 0;
	img->sprite_cal.trans_y = 0;
	img->sprite_cal.screen_x = 0;
	img->sprite_cal.vmscreen = 0;
	img->sprite_cal.sprite_h = 0;
	img->sprite_cal.dw_start_y = 0;
	img->sprite_cal.dw_end_y = 0;
	img->sprite_cal.sprite_w = 0;
	img->sprite_cal.dw_start_x = 0;
	img->sprite_cal.dw_end_x = 0;
}

void	ray_init(int x, int w, t_data *img)
{
	img->ray.cm_x = 2 * x / (double)w - 1;
	img->ray.ray_dir_x = img->player.dir_x + img->player.pl_x * img->ray.cm_x;
	img->ray.ray_dir_y = img->player.dir_y + img->player.pl_y * img->ray.cm_x;
	img->ray.mp_x = (int)(img->player.p_x);
	img->ray.mp_y = (int)(img->player.p_y);
	img->ray.dl_di_x = fabs(1 / img->ray.ray_dir_x);
	img->ray.dl_di_y = fabs(1 / img->ray.ray_dir_y);
	img->ray.hit = 0;
}

void	player(t_data *img)
{
	set_py(img);
	img->player.spd = 0.05;
	img->player.rl_spd = 0.05;
}

void	key(t_data *img)
{
	img->key.fd = 0;
	img->key.bk = 0;
	img->key.lt = 0;
	img->key.rt = 0;
	img->key.rrt = 0;
	img->key.rlt = 0;
}

void	zbuffer_init(t_data *img)
{
	img->zbuffer = (double *)malloc(sizeof(double) * img->map.window_width);
}
