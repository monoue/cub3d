/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 14:08:13 by sperrin           #+#    #+#             */
/*   Updated: 2020/10/22 14:52:22 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_atoi_p(char **map, t_env *e)
{
	int		i;
	int		j;
	int		x;
	int		y;

	x = 0;
	i = 0;
	while (map[i])
	{
		y = 0;
		j = 0;
		while (map[i][j])
		{
			while (map[i][j] == ' ')
				j++;
			if (map[i][j])
				e->map_c[x][y++] = map[i][j++] - '0';
		}
		j = 0;
		i++;
		x++;
	}
}

void		checkmap(t_env *e, int x, int y, int i)
{
	if (e->map_c[x][y] == 1 || e->map_c[x][y] == 3 || e->map_c[x][y] == 4)
		return ;
	if (x == 0 || y == 0 || x == i)
		put_error("ERROR\nMAP NOT CLOSED AROUND SPAWN DUDE\n");
	if (e->map_c[x][y] == -1)
		put_error("ERROR\nMAP NOT CLOSED AROUND SPAWN DUDE\n");
	if (e->map_c[x][y] == 0)
		e->map_c[x][y] = 3;
	if (e->map_c[x][y] == 2)
		e->map_c[x][y] = 4;
	checkmap(e, x + 1, y, i);
	checkmap(e, x, y + 1, i);
	checkmap(e, x - 1, y, i);
	checkmap(e, x, y - 1, i);
}

void		init_map(t_env *e)
{
	int i;
	int j;

	i = 0;
	e->map_c = malloc((e->p.mapx + 1) * sizeof(int *));
	while (i <= e->p.mapx)
	{
		e->map_c[i] = malloc((e->p.mapy + 1) * sizeof(int));
		j = 0;
		while (j <= e->p.mapy)
		{
			e->map_c[i][j] = -1;
			j++;
		}
		i++;
	}
}

void		check(t_env *e)
{
	int i;

	i = 0;
	while (e->map[i])
		i++;
	init_map(e);
	ft_atoi_p(e->map, e);
	checkmap(e, (int)e->p.posy, (int)e->p.posx, i);
}
