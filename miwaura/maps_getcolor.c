/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_getcolor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 15:01:05 by miwaura           #+#    #+#             */
/*   Updated: 2020/10/14 14:37:39 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_width(t_data *img, char *line, int i)
{
	while (ft_isdigit(line[i]))
	{
		img->map.window_width = img->map.window_width * 10 + line[i] - 48;
		i++;
	}
	return (i);
}

int		get_resolution(t_data *img, char *line)
{
	int i;
	int u[2];

	i = 1;
	u[0] = 0;
	u[1] = 0;
	img->map.elements_num++;
	while (line[i] == ' ')
		i++;
	i = get_width(img, line, i);
	while (line[i] == ' ')
		i++;
	if (!ft_isdigit(line[i]))
		return (0);
	while (ft_isdigit(line[i]))
	{
		img->map.window_height = img->map.window_height * 10 + line[i] - 48;
		i++;
	}
	mlx_get_screen_size(img->mlx, &u[1], &u[0]);
	if (img->map.window_height > u[0])
		img->map.window_height = u[0];
	if (img->map.window_width > u[1])
		img->map.window_width = u[1];
	return (1);
}

char	*ft_strjoin_with_n(char *map, char *line)
{
	char *tmp;

	tmp = map;
	map = ft_strjoin(map, "\n");
	if (!map)
		return (NULL);
	tmp = map;
	map = ft_strjoin(map, line);
	free(tmp);
	if (!map)
		return (NULL);
	return (map);
}

int		line_check(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '0' || line[i] == '1')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int		get_colors(t_data *img, char *line, char c)
{
	int i;
	int sum[3];

	i = 0;
	while (i < 3)
	{
		sum[i] = 0;
		i++;
	}
	i = 2;
	while (line[i] == ' ')
		i++;
	if (get_colors_num(line, i, sum) == 0)
		return (0);
	if (c == 'F')
		img->map.floor_color = sum[0] * 65536 + sum[1] * 256 + sum[2];
	if (c == 'C')
		img->map.ceiling_color = sum[0] * 65536 + sum[1] * 256 + sum[2];
	img->map.elements_num++;
	return (1);
}
