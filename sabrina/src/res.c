/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   res.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 16:54:59 by sperrin           #+#    #+#             */
/*   Updated: 2020/10/11 11:37:07 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_atoi1(char *line, int *i)
{
	int	num;

	num = 0;
	ft_spaceskip(line, i);
	while (line[*i] >= '0' && line[*i] <= '9')
	{
		num = num * 10 + (line[*i] - 48);
		(*i)++;
	}
	return (num);
}

int		ft_res(t_env *e, char *line, int *i)
{
	if (e->res_done)
		put_error("ERROR\nMULTIPLE RESOLUTION INPUTS DUDE\n");
	e->res_done = 1;
	if (e->screen.width != 0 || e->screen.height != 0)
		return (-3);
	(*i)++;
	e->screen.width = ft_atoi1(line, i);
	if (line[*i] != ' ')
		put_error("ERROR\nNOT HEIGHT INPUT DUDE\n");
	e->screen.height = ft_atoi1(line, i);
	if (e->screen.height <= 0 || e->screen.width <= 0)
		put_error("ERROR\nINCORRECT RESOLUTION VALUES DUDE\n");
	if (line[*i] == ' ')
		put_error("ERROR\nTOO MANY RESOLUTION VALUES DUDE\n");
	if (e->screen.width > 2560)
		e->screen.width = 2560;
	if (e->screen.height > 1440)
		e->screen.height = 1440;
	return (0);
}
