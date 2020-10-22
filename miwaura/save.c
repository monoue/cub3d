/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 15:39:09 by miwaura           #+#    #+#             */
/*   Updated: 2020/10/22 13:19:57 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	header_init(char *cont, int width, int height)
{
	int		size;

	size = width * height * 3 + 54;
	*(unsigned int *)cont = (unsigned int)'B';
	*(unsigned int *)(cont + 1) = (unsigned int)'M';
	*(unsigned int *)(cont + 2) = (unsigned long)size;
	*(unsigned int *)(cont + 6) = (unsigned int)0;
	*(unsigned int *)(cont + 8) = (unsigned int)0;
	*(unsigned int *)(cont + 10) = (unsigned int)54;
	*(unsigned int *)(cont + 14) = (unsigned long)40;
	*(unsigned int *)(cont + 18) = (long)width;
	*(unsigned int *)(cont + 22) = (long)-height;
	*(unsigned int *)(cont + 26) = (unsigned int)1;
	*(unsigned int *)(cont + 28) = (unsigned int)24;
	*(unsigned int *)(cont + 30) = (unsigned long)0;
	*(unsigned int *)(cont + 34) = (unsigned long)(size - 54);
	*(unsigned int *)(cont + 38) = (long)0;
	*(unsigned int *)(cont + 42) = (long)0;
	*(unsigned int *)(cont + 46) = (unsigned long)0;
	*(unsigned int *)(cont + 50) = (unsigned long)0;
}

void	header_data(t_data img, char *cont, int width, int height)
{
	char	*color;
	int		now;
	int		utils[3];

	header_init(cont, width, height);
	now = 54;
	utils[1] = 0;
	while (utils[1] < height)
	{
		utils[0] = 0;
		while (utils[0] < width)
		{
			color = img.addr + utils[0] * (img.bits_per_pixel / 8)\
			+ (utils[1] * img.line_length);
			*(unsigned char *)(cont + now++) = *(unsigned char *)color++;
			*(unsigned char *)(cont + now++) = *(unsigned char *)color++;
			*(unsigned char *)(cont + now++) = *(unsigned char *)color++;
			utils[0]++;
		}
		utils[2] = width % 4;
		while (utils[2]--)
			*(cont + now++) = 0;
		utils[1]++;
	}
}

void	write_image(t_data img)
{
	int		fd;
	char	*cont;
	int		padding;

	fd = open("bitmap.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	padding = (img.map.window_width * 3) % 4;
	cont = malloc((img.map.window_width + padding) * img.map.window_height * 3 + 54 + 1);
	header_data(img, cont, img.map.window_width, img.map.window_height);
	write(fd, cont, (img.map.window_width + padding) * img.map.window_height * 3 + 54);
	close(fd);
}

void	inits(t_data *img)
{
	player(img);
	key(img);
	set_textures(img);
	zbuffer_init(img);
}

void	save_picture(char *file)
{
	t_data	img;
	int		x;

	set_cubfile_data(&img, file);
	img.mlx = mlx_init();
	img.img = mlx_new_image(img.mlx, img.map.window_width, img.map.window_height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,\
	&img.line_length, &img.endian);
	inits(&img);
	x = 0;
	ray_cast(&img, x);
	sprite_init(&img);
	while (x < img.sprite_num)
	{
		img.sprite[x].order = x;
		img.sprite[x].distance = ((img.player.p_x - img.sprite[x].x) *\
		(img.player.p_x - img.sprite[x].x) + (img.player.p_y - img.sprite[x].y)\
		* (img.player.p_y - img.sprite[x].y));
		x++;
	}
	sort_sprite(&img);
	x = 0;
	sprites(&img, x);
	write_image(img);
}
