/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 14:55:11 by miwaura           #+#    #+#             */
/*   Updated: 2020/10/22 14:09:35 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_map_in(char *line, char *map, int flag)
{
	char *tmp;

	tmp = NULL;
	if (line_check(line))
	{
		tmp = map;
		if (flag == 0)
			map = ft_strjoin(map, line);
		else
			map = ft_strjoin_with_n(map, line);
		if (!map)
		{
			free(tmp);
			return (NULL);
		}
		free(tmp);
	}
	(void)tmp;
	return (map);
}

void	set_py_etc(t_data *img)
{
	if (img->player.dir == 'N')
	{
		img->player.dir_x = 0;
		img->player.dir_y = -1;
		img->player.pl_x = -0.66;
		img->player.pl_y = 0;
	}
	else if (img->player.dir == 'S')
	{
		img->player.dir_x = 0;
		img->player.dir_y = 1;
		img->player.pl_x = 0.66;
		img->player.pl_y = 0;
	}
}

void	set_py(t_data *img)
{
	if (img->player.dir == 'W')
	{
		img->player.dir_x = -1;
		img->player.dir_y = 0;
		img->player.pl_x = 0;
		img->player.pl_y = 0.66;
	}
	else if (img->player.dir == 'E')
	{
		img->player.dir_x = 1;
		img->player.dir_y = 0;
		img->player.pl_x = 0;
		img->player.pl_y = -0.66;
	}
	else if (img->player.dir == 'S')
	{
		set_py_etc(img);
	}
	else if (img->player.dir == 'N')
	{
		set_py_etc(img);
	}
}

void	get_inf_sprite_num(t_data *img)
{
	int i;
	int j;

	i = 0;
	img->sprite_num = 0;
	img->player.p_x = 0;
	img->player.p_y = 0;
	while (img->w_map[i])
	{
		j = 0;
		while (img->w_map[i][j])
		{
			if (img->w_map[i][j] == '2')
				img->sprite_num++;
			if (img->w_map[i][j] == 'N' || img->w_map[i][j] == 'S' ||\
			img->w_map[i][j] == 'W' || img->w_map[i][j] == 'E')
			{
				img->player.p_x = j;
				img->player.p_y = i;
				img->player.dir = img->w_map[i][j];
			}
			j++;
		}
		i++;
	}
}

int		create_map_array(t_data *img, char *line)
{
	char	*map;
	char	*tmp;
	int		utils[3];

	map = ft_strdup("");
	tmp = map;
	utils[1] = 0;
	utils[2] = 0;
	while ((utils[0] = get_next_line(img->fd, &line)) > 0)
	{
		if (line[0] == '\0')
			error_map("invalid map\n", line, map);
		map = get_map_in(line, map, utils[1]);
		utils[1] = 1;
		if (utils[2]++ > 50 || ft_strlen(line) > 50)
			error_map("large file\n", line, map);
		free(line);
	}
	map = get_map_in(line, map, utils[1]);
	img->w_map = ft_split(map, '\n');
	img->w_map_c = ft_split(map, '\n');
	free(map);
	get_inf_sprite_num(img);
	free(line);
	return (1);
}
