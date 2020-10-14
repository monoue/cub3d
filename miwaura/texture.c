/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 15:51:05 by miwaura           #+#    #+#             */
/*   Updated: 2020/10/14 13:39:04 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_texture_w(t_data *img, char *line)
{
	int		i;
	char	*ptr;

	img->map.elements_num++;
	i = 3;
	ptr = NULL;
	while (line[i] == ' ')
		i++;
	if (case_w(img, line, i, ptr) == 1)
		return (1);
	else if (ft_strncmp(line + i, "./textures/bluestone.xpm", 24) == 0)
	{
		w_texture_set(img, ptr, "./textures/bluestone.xpm");
		return (1);
	}
	else if (ft_strncmp(line + i, "./textures/colorstone.xpm", 25) == 0)
	{
		w_texture_set(img, ptr, "./textures/colorstone.xpm");
		return (1);
	}
	return (0);
}

int		case_e(t_data *img, char *line, int i, char *ptr)
{
	if (ft_strncmp(line + i, "./textures/redbrick.xpm", 23) == 0)
	{
		e_texture_set(img, ptr, "./textures/redbrick.xpm");
		return (1);
	}
	if (ft_strncmp(line + i, "./textures/greystone.xpm", 24) == 0)
	{
		e_texture_set(img, ptr, "./textures/greystone.xpm");
		return (1);
	}
	return (0);
}

int		get_texture_e(t_data *img, char *line)
{
	int		i;
	char	*ptr;

	img->map.elements_num++;
	i = 3;
	ptr = NULL;
	while (line[i] == ' ')
		i++;
	if (case_e(img, line, i, ptr) == 1)
		return (1);
	if (ft_strncmp(line + i, "./textures/bluestone.xpm", 24) == 0)
	{
		e_texture_set(img, ptr, "./textures/bluestone.xpm");
		return (1);
	}
	if (ft_strncmp(line + i, "./textures/colorstone.xpm", 25) == 0)
	{
		e_texture_set(img, ptr, "./textures/colorstone.xpm");
		return (1);
	}
	return (0);
}

void	texture_cal(t_data *img, int x)
{
	texture_start_end(img);
	img->texture.texnum = ft_atoi(&img->w_map\
	[img->ray.mp_y][img->ray.mp_x]) - 1;
	if (img->ray.side == 0 || img->ray.side == 1)
		img->texture.wall_x = img->player.p_y +\
		img->ray.p_w_di * img->ray.ray_dir_y;
	else
		img->texture.wall_x = img->player.p_x +\
		img->ray.p_w_di * img->ray.ray_dir_x;
	img->texture.wall_x -= floor((img->texture.wall_x));
	img->texture.tex_x = (int)(img->texture.wall_x * (double)TEX_WIDTH);
	if ((img->ray.side == 0 || img->ray.side == 1) && img->ray.ray_dir_x > 0)
		img->texture.tex_x = TEX_WIDTH - img->texture.tex_x - 1;
	if ((img->ray.side == 2 || img->ray.side == 3) && img->ray.ray_dir_y < 0)
		img->texture.tex_x = TEX_WIDTH - img->texture.tex_x - 1;
	img->texture.step = 1.0 * TEX_HEIGHT / img->texture.line_height;
	img->texture.texpos = (img->texture.draw_start - img->map.window_height /\
	2 + img->texture.line_height / 2) * img->texture.step;
	img->texture.y = img->texture.draw_start;
	texture_wall(img, x);
	texture_celling_floor(img, x);
	img->zbuffer[x] = 0;
	img->zbuffer[x] = img->ray.p_w_di;
}

void	texture_wall(t_data *img, int x)
{
	while (img->texture.y < img->texture.draw_end)
	{
		img->texture.tex_y = (int)img->texture.texpos & (TEX_HEIGHT - 1);
		if (img->ray.side == 0)
			img->texture.dst = img->tex[WALL_N].addr + (img->texture.tex_y *\
			img->tex[WALL_N].line_length + img->texture.tex_x *\
			(img->tex[WALL_N].b_per_pix / 8));
		else if (img->ray.side == 1)
			img->texture.dst = img->tex[WALL_S].addr + (img->texture.tex_y *\
			img->tex[WALL_S].line_length + img->texture.tex_x *\
			(img->tex[WALL_S].b_per_pix / 8));
		else if (img->ray.side == 2)
			img->texture.dst = img->tex[WALL_W].addr + (img->texture.tex_y *\
			img->tex[WALL_W].line_length + img->texture.tex_x *\
			(img->tex[WALL_W].b_per_pix / 8));
		else if (img->ray.side == 3)
			img->texture.dst = img->tex[WALL_E].addr + (img->texture.tex_y *\
			img->tex[WALL_E].line_length + img->texture.tex_x *\
			(img->tex[WALL_E].b_per_pix / 8));
		img->texture.color = *(unsigned int *)img->texture.dst;
		my_mlx_pixel_put(img, x, img->texture.y, img->texture.color);
		img->texture.texpos += img->texture.step;
		img->texture.y++;
	}
}
