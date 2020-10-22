/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 10:41:01 by sperrin           #+#    #+#             */
/*   Updated: 2020/10/10 20:15:55 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		free_tab(t_env **e)
{
	int	i;

	i = 0;
	while ((*e)->map[i])
	{
		free((*e)->map[i]);
		(*e)->map[i] = NULL;
		i++;
	}
	free((*e)->map);
	(*e)->map = NULL;
}

int			destroy_img(t_env *e)
{
	free_tab(&e);
	mlx_destroy_image(e->mlx, e->img);
	mlx_destroy_window(e->mlx, e->screen.win);
	exit(1);
	return (1);
}
