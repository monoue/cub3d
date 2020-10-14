/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 14:56:34 by miwaura           #+#    #+#             */
/*   Updated: 2020/10/14 13:27:50 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(t_data *img)
{
	int i;

	i = 0;
	while (img->w_map[i])
	{
		free(img->w_map[i]);
		i++;
	}
	i = 0;
	while (img->w_map_c[i])
	{
		free(img->w_map_c[i]);
		i++;
	}
}

void	free_reads(t_data *img)
{
	free_map(img);
}

int		finish_program(t_data *img)
{
	free_reads(img);
	mlx_destroy_window(img->mlx, img->win);
	mlx_destroy_image(img->mlx, img->img);
	exit(0);
}
