/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/07 16:03:29 by sperrin           #+#    #+#             */
/*   Updated: 2020/10/21 13:38:17 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_slist(t_env *e)
{
	int		i;
	int		j;
	int		k;

	if (!(e->sprites = malloc(sizeof(t_spriteptr) * e->p.spr)))
		put_error("ERROR\nMALLOC FAILLED DUDE\n");
	if (!(e->spr_order = (malloc(e->p.spr * sizeof(int)))))
		put_error("ERROR\nMALLOC FAILLED DUDE\n");
	i = 0;
	j = 0;
	while (j < e->p.mapy)
	{
		k = 0;
		while (k < e->p.mapx)
		{
			if (e->map[j][k] == '2')
			{
				e->sprites[i].y = (double)j + 0.5;
				e->sprites[i++].x = (double)k + 0.5;
			}
			k++;
		}
		j++;
	}
	return (1);
}

void	ft_pos3(t_env *e, char c)
{
	if (c == 'N')
	{
		e->p.dirx = 0;
		e->p.diry = -1;
		e->p.planex = 0.66;
		e->p.planey = 0;
	}
	else if (c == 'S')
	{
		e->p.dirx = 0;
		e->p.diry = 1;
		e->p.planex = -0.66;
		e->p.planey = 0;
	}
}

void	ft_pos2(t_env *e, char c)
{
	if (c == 'E')
	{
		e->p.dirx = 1;
		e->p.diry = 0;
		e->p.planex = 0;
		e->p.planey = -0.66;
	}
	else if (c == 'W')
	{
		e->p.dirx = -1;
		e->p.diry = 0;
		e->p.planex = 0;
		e->p.planey = 0.66;
	}
}

void	ft_pos_bis(t_env *e)
{
	if (e->spawn_done)
		put_error("ERROR\nMULTIPLE SPAWNPOINT DUDE\n");
	e->spawn_done = 1;
}

void	ft_pos(t_env *e)
{
	char	c;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!e->map)
		put_error("ERROR\nNOT MAP DUDE\n");
	while (++i < e->p.mapy)
	{
		while (++j < e->p.mapx)
		{
			c = e->map[i][j];
			if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
			{
				ft_pos_bis(e);
				e->p.posy = (double)i + 0.5;
				e->p.posx = (double)j + 0.5;
				ft_pos2(e, c);
				ft_pos3(e, c);
			}
		}
		j = -1;
	}
}
