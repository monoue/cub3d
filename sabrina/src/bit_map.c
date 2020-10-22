/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bit_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 14:11:57 by sperrin           #+#    #+#             */
/*   Updated: 2020/10/16 12:30:41 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_bdata(t_env *e, int fd)
{
	int				i;
	int				j;
	unsigned char	buffer[4];

	i = e->screen.width * (e->screen.height - 1);
	while (i >= 0)
	{
		j = 0;
		while (j < e->screen.width)
		{
			buffer[0] = (unsigned char)(e->edit[i] % 256);
			buffer[1] = (unsigned char)(e->edit[i] / 256 % 256);
			buffer[2] = (unsigned char)(e->edit[i] / 256 / 256 % 256);
			buffer[3] = (unsigned char)(0);
			write(fd, buffer, 4);
			i++;
			j++;
		}
		i -= 2 * e->screen.width;
	}
}

void	ft_binfo(t_env *e, int fd)
{
	int				n;
	unsigned char	header[40];

	n = 0;
	while (n < 40)
		header[n++] = (unsigned char)(0);
	header[0] = (unsigned char)(40);
	n = e->screen.width;
	header[4] = (unsigned char)(n % 256);
	header[5] = (unsigned char)(n / 256 % 256);
	header[6] = (unsigned char)(n / 256 / 256 % 256);
	header[7] = (unsigned char)(n / 256 / 256 / 256);
	n = e->screen.height;
	header[8] = (unsigned char)(n % 256);
	header[9] = (unsigned char)(n / 256 % 256);
	header[10] = (unsigned char)(n / 256 / 256 % 256);
	header[11] = (unsigned char)(n / 256 / 256 / 256);
	header[12] = (unsigned char)(1);
	header[14] = (unsigned char)(32);
	write(fd, header, 40);
}

void	ft_bfile(t_env *e, int fd)
{
	int				n;
	unsigned char	header[14];

	n = 0;
	while (n < 14)
		header[n++] = (unsigned char)(0);
	header[0] = (unsigned char)(66);
	header[1] = (unsigned char)(77);
	n = e->screen.width * e->screen.height * 4 + 54;
	header[2] = (unsigned char)(n % 256);
	header[3] = (unsigned char)(n / 256 % 256);
	header[4] = (unsigned char)(n / 256 / 256 % 256);
	header[5] = (unsigned char)(n / 256 / 256 / 256);
	header[10] = (unsigned char)(54);
	write(fd, header, 14);
}

int		take_screenshot(t_env *e)
{
	int		fd;

	draw_wolf(e);
	fd = open("bitmap.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	ft_bfile(e, fd);
	ft_binfo(e, fd);
	ft_bdata(e, fd);
	close(fd);
	free(e->mlx);
	free(e->edit);
	return (1);
}

void	make_screenshot(t_env *e)
{
	e->screenshot = 1;
	if (!take_screenshot(e))
		put_error("ERROR\nCouldn't create/open screenshot.bmp\n");
	write(1, "Screenshot saved!\n", 18);
	exit(1);
}
