/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 10:41:20 by sperrin           #+#    #+#             */
/*   Updated: 2020/10/13 18:26:35 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_error(char *message)
{
	int i;

	i = 0;
	write(2, message, ft_strlen(message));
	exit(1);
}

int		ft_namecheck(char *arg, char *ext)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
		i++;
	if ((i > 4 && arg[i - 1] == ext[2] && arg[i - 2] == ext[1])
		&& (arg[i - 3] == ext[0] && arg[i - 4] == '.'))
		return (1);
	return (0);
}

int		ft_savecheck(char *arg, char *save)
{
	int	i;

	i = 0;
	while (arg[i] == save[i])
	{
		if (arg[i] == '\0' && save[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}

void	text_error(t_env *e)
{
	if (!e->s_done)
		put_error("ERROR\nNOT SPRITES TEXTURES DUDE\n");
	if (!e->floor_done)
		put_error("ERROR\nNOT FLOOR COLORS DUDE\n");
	if (!e->sky_done)
		put_error("ERROR\nNOT CEILING COLORS DUDE\n");
	if (!e->so_done)
		put_error("ERROR\nNOT SOUTH TEXTURES DUDE\n");
	if (!e->we_done)
		put_error("ERROR\nNOT WEST TEXTURES DUDE\n");
	if (!e->ea_done)
		put_error("ERROR\nNOT EAST TEXTURES DUDE\n");
	if (!e->no_done)
		put_error("ERROR\nNOT NORTH TEXTURES DUDE\n");
	if (!e->res_done)
		put_error("ERROR\nNOT RESOLUTION INPUTS DUDE\n");
}
