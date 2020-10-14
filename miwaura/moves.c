/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwaura <miwaura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 15:32:24 by miwaura           #+#    #+#             */
/*   Updated: 2020/09/16 15:33:49 by miwaura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_front(t_data *img)
{
	if (img->w_map[(int)img->player.p_y][(int)(img->player.p_x +
	img->player.dir_x * img->player.spd)] != '1')
	{
		img->player.p_x += img->player.dir_x * img->player.spd;
	}
	if (img->w_map[(int)(img->player.p_y + img->player.dir_y *
	img->player.spd)][(int)img->player.p_x] != '1')
	{
		img->player.p_y += img->player.dir_y * img->player.spd;
	}
}

void	move_back(t_data *img)
{
	if (img->w_map[(int)img->player.p_y]\
	[(int)(img->player.p_x - img->player.dir_x * img->player.spd)] != '1')
	{
		img->player.p_x -= img->player.dir_x * img->player.spd;
	}
	if (img->w_map[(int)(img->player.p_y - img->player.dir_y *\
	img->player.spd)][(int)img->player.p_x] != '1')
		img->player.p_y -= img->player.dir_y * img->player.spd;
}

void	move_left(t_data *img)
{
	if (img->w_map[(int)img->player.p_y]\
	[(int)(img->player.p_x - img->player.pl_x * img->player.spd)] != '1')
		img->player.p_x -= img->player.pl_x * img->player.spd;
	if (img->w_map[(int)(img->player.p_y - img->player.pl_y * img->player.spd)]\
	[(int)img->player.p_x] != '1')
		img->player.p_y -= img->player.pl_y * img->player.spd;
}

void	move_right(t_data *img)
{
	if (img->w_map[(int)img->player.p_y]\
	[(int)(img->player.p_x + img->player.pl_x * img->player.spd)] != '1')
		img->player.p_x += img->player.pl_x * img->player.spd;
	if (img->w_map[(int)(img->player.p_y + img->player.pl_y * img->player.spd)]\
	[(int)img->player.p_x] != '1')
		img->player.p_y += img->player.pl_y * img->player.spd;
}
