/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 15:06:13 by miwaura           #+#    #+#             */
/*   Updated: 2020/10/15 10:36:55 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		up(t_data *img, int row, int col)
{
	int i;

	i = 0;
	if (row < 0)
		return (1);
	while (img->w_map_c[row][i])
		i++;
	if (i <= col)
		return (1);
	if (img->w_map_c[row][i] == ' ')
		return (1);
	return (0);
}

int		down(t_data *img, int row, int col)
{
	int i;

	i = 0;
	while (img->w_map_c[i])
		i++;
	if (i <= row)
		return (1);
	i = 0;
	while (img->w_map_c[row][i])
		i++;
	if (i <= col)
		return (1);
	if (img->w_map_c[row][i] == ' ')
		return (1);
	return (0);
}

int		right(t_data *img, int row, int col)
{
	int i;

	i = 0;
	while (img->w_map_c[row][i])
		i++;
	if (i <= col)
		return (1);
	i = 0;
	if (img->w_map_c[row][col] == ' ')
		return (1);
	return (0);
}

void	fill(t_data *img, int row, int col, int i)
{
	if (row < 0 || row == i || col < 0 || img->w_map_c[row][col] == ' ')
		return ;
	if (img->w_map_c[row][col] == '1')
		return ;
	if (!(img->w_map_c[row][col] == 'N' || img->w_map_c[row][col] == 'W'\
	|| img->w_map_c[row][col] == 'E' || img->w_map_c[row][col] == 'S' ||\
	img->w_map_c[row][col] == '0' || img->w_map_c[row][col] == '2'))
		return ;
	if (img->flag == 1)
		return ;
	if (row == 0 || col == 0 || row == i ||\
	col == (int)(ft_strlen(img->w_map_c[row]) - 1))
		img->flag = 1;
	if (up(img, row - 1, col) == 1 || down(img, row + 1, col) == 1 ||\
	right(img, row, col + 1) == 1 || right(img, row, col - 1) == 1)
		img->flag = 1;
	img->w_map_c[row][col] = 'x';
	fill(img, row + 1, col, i);
	fill(img, row - 1, col, i);
	fill(img, row, col + 1, i);
	fill(img, row, col - 1, i);
}

void	check(t_data *img)
{
	int i;

	i = 0;
	img->flag = 0;
	while (img->w_map_c[i])
		i++;
	fill(img, (int)img->player.p_y, (int)img->player.p_x, i);
	i = 0;
	if (img->flag == 1)
	{
		exit_failure_with_err_msg("invalid map\n");
		exit(0);
	}
}
