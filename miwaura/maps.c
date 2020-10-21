/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 15:04:36 by miwaura           #+#    #+#             */
/*   Updated: 2020/10/21 09:50:22 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_elements_check(t_data *img)
{
	if (img->map.window_width == 0 || img->map.window_height == 0\
	|| img->map.north_texture_path == NULL)
	{
		free_reads(img);
		put_err_msg("elements\n");
		exit(0);
	}
	if (img->map.south_texture_path == NULL || img->map.west_texture_path == NULL)
	{
		free_reads(img);
		put_err_msg("elements\n");
		exit(0);
	}
	if (img->map.east_texture_path == NULL || img->map.sprite_texture_path == NULL\
	|| img->map.elements_num != 8)
	{
		free_reads(img);
		put_err_msg("elements\n");
		exit(0);
	}
}

void	read_map_open(t_data *img, char *file)
{
	char	*line;
	int		rv;

	map_init(img);
	if ((img->fd = open(file, O_RDONLY)) == -1)
		exit_failure_closing_fd("open file", img->fd);
	rv = 0;
	while (get_next_line(img->fd, &line) > 0)
	{
		rv = get_cubfile_info(img, line);
		if (rv == 0)
			img->flag = 1;
		free(line);
	}
	free(line);
	map_elements_check(img);
	img->sprite = (t_sprite *)malloc(sizeof(t_sprite) * img->sprite_num);
	if (img->flag == 1)
	{
		free_reads(img);
		put_err_msg("map");
		exit(0);
	}
	get_inf_sprite_pos(img);
	check(img);
}

void	map_init(t_data *img)
{
	img->map.window_width = 0;
	img->map.window_height = 0;
	img->map.north_texture_path = NULL;
	img->map.south_texture_path = NULL;
	img->map.west_texture_path = NULL;
	img->map.east_texture_path = NULL;
	img->map.sprite_texture_path = NULL;
	img->map.floor_color = 0;
	img->map.elements_num = 0;
	img->map.ceiling_color = 0;
	img->flag = 0;
}

int		get_cubfile_info(t_data *img, char *line)
{
	if (ft_strncmp(line, "R ", 2) == 0)
		return (get_resolution(img, line));
	else if (ft_strncmp(line, "NO ", 3) == 0)
		return (get_texture_n(img, line));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		return (get_texture_s(img, line));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		return (get_texture_w(img, line));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		return (get_texture_e(img, line));
	else if (ft_strncmp(line, "S ", 2) == 0)
		return (get_sprite(img, line));
	else if (ft_strncmp(line, "F ", 2) == 0)
		return (get_colors(img, line, 'F'));
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (get_colors(img, line, 'C'));
	else if (mapline(line) == 0)
		return (get_map(img, line));
	return (1);
}

int		get_colors_num(char *line, int i, int *sum)
{
	int j;

	j = 0;
	while (j < 3)
	{
		if (line[i] == ',')
			i++;
		while (ft_isdigit(line[i]))
		{
			sum[j] = sum[j] * 10 + (line[i] - 48);
			if (sum[j] > 255)
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}
