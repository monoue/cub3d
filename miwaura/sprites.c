/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 13:23:32 by miwaura           #+#    #+#             */
/*   Updated: 2020/10/14 13:39:04 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_sprite_utils(t_data *img, int i)
{
	int		tmp;
	double	dtmp;
	int		k;

	k = 0;
	while (k < img->sprite_num - 1)
	{
		i = 0;
		while (i < img->sprite_num - 1 - k)
		{
			if (img->sprite[i].distance < img->sprite[i + 1].distance)
			{
				dtmp = img->sprite[i].distance;
				img->sprite[i].distance = img->sprite[i + 1].distance;
				img->sprite[i + 1].distance = dtmp;
				tmp = img->sprite[i].order;
				img->sprite[i].order = img->sprite[i + 1].order;
				img->sprite[i + 1].order = tmp;
			}
			i++;
		}
		k++;
	}
}

void	sort_sprite(t_data *img)
{
	int i;

	i = 0;
	while (i < img->sprite_num)
	{
		img->sprite[i].order = i;
		img->sprite[i].distance = ((img->player.p_x - img->sprite[i].x)\
		* (img->player.p_x - img->sprite[i].x) + (img->player.p_y -\
		img->sprite[i].y) * (img->player.p_y - img->sprite[i].y));
		i++;
	}
	i = 0;
	sort_sprite_utils(img, i);
}

void	sprite_calculation_first(t_data *img, int x)
{
	img->sprite_cal.sprite_x = img->sprite[img->sprite[x].order].x\
	+ 0.5 - img->player.p_x;
	img->sprite_cal.sprite_y = img->sprite[img->sprite[x].order].y\
	+ 0.5 - img->player.p_y;
	img->sprite_cal.invdet = 1.0 / (img->player.pl_x *\
	img->player.dir_y - img->player.dir_x * img->player.pl_y);
	img->sprite_cal.trans_x = img->sprite_cal.invdet *\
	(img->player.dir_y * img->sprite_cal.sprite_x -\
	img->player.dir_x * img->sprite_cal.sprite_y);
	img->sprite_cal.trans_y = img->sprite_cal.invdet *\
	((-img->player.pl_y) * img->sprite_cal.sprite_x +\
	img->player.pl_x * img->sprite_cal.sprite_y);
	img->sprite_cal.screen_x = (int)((img->map.window_width / 2)\
	* (1 + img->sprite_cal.trans_x / img->sprite_cal.trans_y));
	img->sprite_cal.vmscreen = (int)(VMOVE / img->sprite_cal.trans_y);
	img->sprite_cal.sprite_h = abs((int)(img->map.window_height /\
	(img->sprite_cal.trans_y)));
	img->sprite_cal.dw_start_y = -img->sprite_cal.sprite_h /\
	2 + img->map.window_height / 2 + img->sprite_cal.vmscreen;
}

void	sprite_calculation(t_data *img, int x)
{
	sprite_calculation_first(img, x);
	if (img->sprite_cal.dw_start_y < 0)
		img->sprite_cal.dw_start_y = 0;
	img->sprite_cal.dw_end_y = img->sprite_cal.sprite_h /\
	2 + img->map.window_height / 2 + img->sprite_cal.vmscreen;
	if (img->sprite_cal.dw_end_y >= img->map.window_height)
		img->sprite_cal.dw_end_y = img->map.window_height - 1;
	img->sprite_cal.sprite_w = abs((int)(img->map.window_height\
	/ (img->sprite_cal.trans_y)));
	img->sprite_cal.dw_start_x = -img->sprite_cal.sprite_w\
	/ 2 + img->sprite_cal.screen_x;
	if (img->sprite_cal.dw_start_x < 0)
		img->sprite_cal.dw_start_x = 0;
	img->sprite_cal.dw_end_x = img->sprite_cal.sprite_w\
	/ 2 + img->sprite_cal.screen_x;
	if (img->sprite_cal.dw_end_x >= img->map.window_width)
		img->sprite_cal.dw_end_x = img->map.window_width - 1;
}
