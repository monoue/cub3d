/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bitmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 09:19:48 by monoue            #+#    #+#             */
/*   Updated: 2020/11/19 10:10:16 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "save_bitmap.h"

void	ft_bdata(int fd)
{
	int				i;
	int				j;
	unsigned char	buffer[4];
	int *addr = (int *)g_img.addr;

	i = g_cubfile_data.window_width * (g_cubfile_data.window_height - 1);
	while (i >= 0)
	{
		j = 0;
		while (j < g_cubfile_data.window_width)
		{
			// buffer[0] = (unsigned char)((int)(g_img.addr[i * 4]) % 256);
			// buffer[1] = (unsigned char)((int)(g_img.addr[i * 4]) / 256 % 256);
			// buffer[2] = (unsigned char)((int)(g_img.addr[i * 4]) / 256 / 256 % 256);
			buffer[0] = (unsigned char)(addr[i] % 256);
			buffer[1] = (unsigned char)(addr[i] / 256 % 256);
			buffer[2] = (unsigned char)(addr[i] / 256 / 256 % 256);
			buffer[3] = (unsigned char)(0);
			write(fd, buffer, 4);
			i++;
			j++;
		}
		i -= 2 * g_cubfile_data.window_width;
	}
}

void	ft_binfo(int fd)
{
	int				n;
	unsigned char	header[40];

	n = 0;
	while (n < 40)
		header[n++] = (unsigned char)(0);
	header[0] = (unsigned char)(40);
	n = g_cubfile_data.window_width;
	header[4] = (unsigned char)(n % 256);
	header[5] = (unsigned char)(n / 256 % 256);
	header[6] = (unsigned char)(n / 256 / 256 % 256);
	header[7] = (unsigned char)(n / 256 / 256 / 256);
	n = g_cubfile_data.window_height;
	header[8] = (unsigned char)(n % 256);
	header[9] = (unsigned char)(n / 256 % 256);
	header[10] = (unsigned char)(n / 256 / 256 % 256);
	header[11] = (unsigned char)(n / 256 / 256 / 256);
	header[12] = (unsigned char)(1);
	header[14] = (unsigned char)(32);
	write(fd, header, 40);
}

void	ft_bfile(int fd)
{
	int				n;
	unsigned char	header[14];

	n = 0;
	while (n < 14)
		header[n++] = (unsigned char)(0);
	header[0] = (unsigned char)(66);
	header[1] = (unsigned char)(77);
	n = g_cubfile_data.window_width * g_cubfile_data.window_height * 4 + 54;
	header[2] = (unsigned char)(n % 256);
	header[3] = (unsigned char)(n / 256 % 256);
	header[4] = (unsigned char)(n / 256 / 256 % 256);
	header[5] = (unsigned char)(n / 256 / 256 / 256);
	header[10] = (unsigned char)(54);
	write(fd, header, 14);
}

int		take_screenshot()
{
	int		fd;

	// draw_wolf(e);
	fd = open("bitmap.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	ft_bfile(fd);
	ft_binfo(fd);
	ft_bdata(fd);
	close(fd);
	// free(e->mlx);
	// free(e->edit);
	return (1);
}

void	make_screenshot()
{
	if (!take_screenshot())
		ft_putstr("hogehoge");
		// put_error("ERROR\nCouldn't create/open screenshot.bmp\n");
	write(1, "Screenshot saved!\n", 18);
	exit(1);
}