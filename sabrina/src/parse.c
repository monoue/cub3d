/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 13:48:46 by sperrin           #+#    #+#             */
/*   Updated: 2020/10/21 13:39:48 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	make_floor(char *str, t_env *e)
{
	if (e->floor_done)
		put_error("ERROR\nMULTIPLE FLOOR COLOR INPUTS DUDE\n");
	e->floor_done = 1;
	while (*str == ' ')
		str++;
	e->fr = ft_cubatoi_f(str);
	while (ft_isdigit(*str) || *str == ' ')
		str++;
	if (*(str++) != ',')
		put_error("ERROR\nWRONG FLOOR COLOR INPUT DUDE\n");
	while (*str == ' ')
		str++;
	e->fg = ft_cubatoi_f(str);
	while (ft_isdigit(*str) || *str == ' ')
		str++;
	if (*(str++) != ',')
		put_error("ERROR\nWRONG FLOOR COLOR INPUT DUDE\n");
	while (*str == ' ')
		str++;
	e->fb = ft_cubatoi_f(str);
	if (e->fb == -1 || e->fg == -1 || e->fr == -1)
		put_error("ERROR\nWRONG VALUES FOR FLOOR COLOR DUDE\n");
}

void	make_sky(char *str, t_env *e)
{
	if (e->sky_done)
		put_error("ERROR\nMULTIPLE CEILING COLOR INPUTS DUDE\n");
	e->sky_done = 1;
	while (*str == ' ')
		str++;
	e->sr = ft_cubatoi_f(str);
	while (ft_isdigit(*str) || *str == ' ')
		str++;
	if (*(str++) != ',')
		put_error("ERROR\nWRONG CEILING COLOR INPUT DUDE\n");
	while (*str == ' ')
		str++;
	e->sg = ft_cubatoi_f(str);
	while (ft_isdigit(*str) || *str == ' ')
		str++;
	if (*(str++) != ',')
		put_error("ERROR\nWRONG CEILING COLOR INPUT DUDE\n");
	while (*str == ' ')
		str++;
	e->sb = ft_cubatoi_f(str);
	while (ft_isdigit(*str) || *str == ' ')
		str++;
	if (*str || e->sb == -1 || e->sr == -1 || e->sg == -1)
		put_error("ERROR\nWRONG VALUES FOR CEILINGCOLOR DUDE\n");
}

void	ft_line2(t_env *e, char *line, int i)
{
	if (e->map_up == 0 && (line[i] == '1' || line[i] == '0'))
		put_error("ERROR\nTHE MAP IS NOT IN THE RIGHT PLACE DUDE\n");
}

void	ft_line(t_env *e, char *line, int i, int a)
{
	ft_spaceskip(line, &i);
	ft_line2(e, line, i);
	if ((line[i] == '1' || line[i] == '0') && line[i] != '\0')
		ft_map(e, line, &a);
	else if (line[i] == 'R' && line[i + 1] == ' ')
		ft_res(e, line, &i);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		make_floor(line + 1, e);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		make_sky(line + 1, e);
	else if (line[i] == 'N' && line[i + 1] == 'O')
		txt_init(1, line + 2, e);
	else if (line[i] == 'S' && line[i + 1] == 'O')
		txt_init(2, line + 2, e);
	else if (line[i] == 'W' && line[i + 1] == 'E')
		txt_init(4, line + 2, e);
	else if (line[i] == 'E' && line[i + 1] == 'A')
		txt_init(3, line + 2, e);
	else if (line[i] == 'S' && line[i + 1] == ' ')
		txt_init(5, line + 2, e);
	else if (line[i] == '\0' && e->check == 1)
		put_error("ERROR\nNEW LINE IN MAP DUDE\n");
	else if (line[i])
		put_error("ERROR\nWRONG IDENTIFIER DUDE\n");
	e->map_up = 1;
}

int		read_file(t_env *e, char *cub)
{
	char	*line;

	e->fd = open(cub, O_RDONLY);
	if (e->fd == -1)
		put_error("ERROR\nNOT FILE DUDE\n");
	e->check = 0;
	while (get_next_line(e->fd, &line) > 0)
	{
		ft_line(e, line, 0, 0);
		free(line);
	}
	e->check = 0;
	ft_line(e, line, 0, 0);
	free(line);
	close(e->fd);
	text_error(e);
	ft_pos(e);
	if (e->p.posx == 0 || e->p.posy == 0)
		put_error("ERROR\nNOT SPAWNPOINT DUDE\n");
	e->sprites = NULL;
	ft_slist(e);
	check(e);
	return (1);
}
