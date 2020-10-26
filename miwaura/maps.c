/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 15:04:36 by miwaura           #+#    #+#             */
/*   Updated: 2020/10/26 14:36:13 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_elements_check(t_data *img)
{
	if (img->map.window_width == 0 || img->map.window_height == 0\
	|| img->map.n_tex_path == NULL)
	{
		free_reads(img);
		put_err_msg("elements\n");
		exit(0);
	}
	if (img->map.s_tex_path == NULL || img->map.w_tex_path == NULL)
	{
		free_reads(img);
		put_err_msg("elements\n");
		exit(0);
	}
	if (img->map.e_tex_path == NULL || img->map.sprite_tex_path == NULL\
	|| img->map.elements_num != 8)
	{
		free_reads(img);
		put_err_msg("elements\n");
		exit(0);
	}
}

void	set_cubfile_data(t_data *img, char *file)
{
	char	*line;
	int		rv;

	map_init(img);
	if ((img->fd = open(file, O_RDONLY)) == -1)
		exit_failure_closing_fd("open file", img->fd);
	rv = 0;
	while (get_next_line(img->fd, &line) > 0)
	{
		rv = get_line_data(img, line);
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
	get_sprites_positions(img);
	check(img);
}

void	map_init(t_data *img)
{
	img->map.window_width = 0;
	img->map.window_height = 0;
	img->map.n_tex_path = NULL;
	img->map.s_tex_path = NULL;
	img->map.w_tex_path = NULL;
	img->map.e_tex_path = NULL;
	img->map.sprite_tex_path = NULL;
	img->map.floor_color = 0;
	img->map.elements_num = 0;
	img->map.ceiling_color = 0;
	img->flag = 0;
}

int		get_line_data(t_data *data, char *cubfile_line)
{
	if (ft_strncmp(cubfile_line, "R ", 2) == 0)
		return (get_resolution(data, cubfile_line));
	else if (ft_strncmp(cubfile_line, "NO ", 3) == 0)
		return (get_texture_n(data, cubfile_line));
	else if (ft_strncmp(cubfile_line, "SO ", 3) == 0)
		return (get_texture_s(data, cubfile_line));
	else if (ft_strncmp(cubfile_line, "WE ", 3) == 0)
		return (get_texture_w(data, cubfile_line));
	else if (ft_strncmp(cubfile_line, "EA ", 3) == 0)
		return (get_texture_e(data, cubfile_line));
	else if (ft_strncmp(cubfile_line, "S ", 2) == 0)
		return (get_sprite(data, cubfile_line));
	else if (ft_strncmp(cubfile_line, "F ", 2) == 0)
		return (get_colors(data, cubfile_line, 'F'));
	else if (ft_strncmp(cubfile_line, "C ", 2) == 0)
		return (get_colors(data, cubfile_line, 'C'));
	else if (mapline(cubfile_line) == 0)
		return (create_map_array(data, cubfile_line));
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
