/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rolls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwaura <miwaura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 15:34:31 by miwaura           #+#    #+#             */
/*   Updated: 2020/09/28 15:33:37 by miwaura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	roll_right(t_data *img)
{
	double oldd_x;
	double oldpl_x;

	oldd_x = img->player.dir_x;
	oldpl_x = img->player.pl_x;
	img->player.dir_x = img->player.dir_x * cos(-img->player.rl_spd)\
	- img->player.dir_y * sin(-img->player.rl_spd);
	img->player.dir_y = oldd_x * sin(-img->player.rl_spd) +\
	img->player.dir_y * cos(-img->player.rl_spd);
	img->player.pl_x = img->player.pl_x * cos(-img->player.rl_spd)\
	- img->player.pl_y * sin(-img->player.rl_spd);
	img->player.pl_y = oldpl_x * sin(-img->player.rl_spd) +\
	img->player.pl_y * cos(-img->player.rl_spd);
}

void	roll_left(t_data *img)
{
	double oldd_x;
	double oldpl_x;

	oldd_x = img->player.dir_x;
	oldpl_x = img->player.pl_x;
	img->player.dir_x = img->player.dir_x * cos(img->player.rl_spd)\
	- img->player.dir_y * sin(img->player.rl_spd);
	img->player.dir_y = oldd_x * sin(img->player.rl_spd) + img->player.dir_y\
	* cos(img->player.rl_spd);
	img->player.pl_x = img->player.pl_x * cos(img->player.rl_spd)\
	- img->player.pl_y * sin(img->player.rl_spd);
	img->player.pl_y = oldpl_x * sin(img->player.rl_spd) +\
	img->player.pl_y * cos(img->player.rl_spd);
}

void	moves(t_data *img)
{
	if (img->key.fd == 1)
		move_front(img);
	if (img->key.bk == 1)
		move_back(img);
	if (img->key.lt == 1)
		move_left(img);
	if (img->key.rt == 1)
		move_right(img);
	if (img->key.rlt == 1)
		roll_left(img);
	if (img->key.rrt == 1)
		roll_right(img);
}

int		mapline(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]))
		{
			return (0);
		}
		i++;
	}
	return (1);
}
