/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 16:09:24 by miwaura           #+#    #+#             */
/*   Updated: 2020/10/14 13:41:20 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		tex_etc(t_data *img)
{
	if (!(img->tex[WALL_W].img_ptr = mlx_xpm_file_to_image(img->mlx,\
	img->map.w_tex_path, &img->tex[WALL_W].w, &img->tex[WALL_W].h)))
		return (0);
	img->tex[WALL_W].addr = mlx_get_data_addr(img->tex[WALL_W].img_ptr,\
	&img->tex[WALL_W].b_per_pix, &img->tex[WALL_W].line_length,\
	&img->tex[0].endian);
	if (!(img->tex[8].img_ptr = mlx_xpm_file_to_image(img->mlx,\
	img->map.sprite_tex_path, &img->tex[8].w, &img->tex[8].h)))
		return (0);
	img->tex[8].addr = mlx_get_data_addr(img->tex[8].img_ptr,\
	&img->tex[8].b_per_pix, &img->tex[8].line_length,\
	&img->tex[0].endian);
	return (1);
}

int		set_textures(t_data *img)
{
	int x;

	if (!(img->tex[WALL_N].img_ptr = mlx_xpm_file_to_image(img->mlx,\
	img->map.n_tex_path, &img->tex[WALL_N].w, &img->tex[WALL_N].h)))
		return (0);
	img->tex[WALL_N].addr = mlx_get_data_addr(img->tex[WALL_N].img_ptr,\
	&img->tex[WALL_N].b_per_pix, &img->tex[WALL_N].line_length,\
	&img->tex[0].endian);
	if (!(img->tex[WALL_S].img_ptr = mlx_xpm_file_to_image(img->mlx,\
	img->map.s_tex_path, &img->tex[WALL_S].w, &img->tex[WALL_S].h)))
		return (0);
	img->tex[WALL_S].addr = mlx_get_data_addr(img->tex[WALL_S].img_ptr,\
	&img->tex[WALL_S].b_per_pix, &img->tex[WALL_S].line_length,\
	&img->tex[0].endian);
	if (!(img->tex[WALL_E].img_ptr = mlx_xpm_file_to_image(img->mlx,\
	img->map.e_tex_path, &img->tex[WALL_E].w, &img->tex[WALL_E].h)))
		return (0);
	img->tex[WALL_E].addr = mlx_get_data_addr(img->tex[WALL_E].img_ptr,\
	&img->tex[WALL_E].b_per_pix, &img->tex[WALL_E].line_length,\
	&img->tex[0].endian);
	x = tex_etc(img);
	if (x == 0)
		return (0);
	return (1);
}

void	texture_celling_floor(t_data *img, int x)
{
	img->texture.y = 0;
	while (img->texture.y++ < img->texture.draw_start)
	{
		my_mlx_pixel_put(img, x, img->texture.y, img->map.ceiling_color);
	}
	img->texture.y = img->texture.draw_end;
	while (img->texture.y++ < img->map.window_height - 1)
	{
		my_mlx_pixel_put(img, x, img->texture.y, img->map.floor_color);
	}
}

void	texture_start_end(t_data *img)
{
	img->texture.line_height = (int)(img->map.window_height / img->ray.p_w_di);
	img->texture.draw_start = -img->texture.line_height /\
	2 + img->map.window_height / 2;
	if (img->texture.draw_start < 0)
		img->texture.draw_start = 0;
	img->texture.draw_end = img->texture.line_height / 2\
	+ img->map.window_height / 2;
	if (img->texture.draw_end >= img->map.window_height)
		img->texture.draw_end = img->map.window_height - 1;
}
