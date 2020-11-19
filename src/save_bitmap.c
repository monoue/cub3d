/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bitmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 09:19:48 by monoue            #+#    #+#             */
/*   Updated: 2020/11/19 13:35:48 by monoue           ###   ########.fr       */
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

void	write_info_header(int fd)
{
	unsigned char	info_header_buf[INFO_HEADER_SIZE];

	ft_bzero(info_header_buf, sizeof(info_header_buf));
	int				n;

	// n = 0;
	// while (n < 40)
	// 	info_header_buf[n++] = (unsigned char)(0);
	info_header_buf[0] = (unsigned char)(40);
	n = g_cubfile_data.window_width;
	info_header_buf[4] = (unsigned char)(n % 256);
	info_header_buf[5] = (unsigned char)(n / 256 % 256);
	info_header_buf[6] = (unsigned char)(n / 256 / 256 % 256);
	info_header_buf[7] = (unsigned char)(n / 256 / 256 / 256);
	n = g_cubfile_data.window_height;
	info_header_buf[8] = (unsigned char)(n % 256);
	info_header_buf[9] = (unsigned char)(n / 256 % 256);
	info_header_buf[10] = (unsigned char)(n / 256 / 256 % 256);
	info_header_buf[11] = (unsigned char)(n / 256 / 256 / 256);
	info_header_buf[12] = (unsigned char)(1);
	info_header_buf[14] = (unsigned char)(32);
	write(fd, info_header_buf, INFO_HEADER_SIZE);
}

void	write_file_header(int fd)
{
	unsigned char	file_header_buf[FILE_HEADER_SIZE];
	const int		real_width = g_cubfile_data.window_width * 3 + g_cubfile_data.window_width % 4;
	const unsigned int	file_size = g_cubfile_data.window_height * real_width + HEADER_SIZE;

	ft_bzero(file_header_buf, sizeof(file_header_buf));
	file_header_buf[FILE_TYPE_1] = 'B';
	file_header_buf[FILE_TYPE_2] = 'M';
	ft_memcpy(&file_header_buf[FILE_SIZE], &file_size, sizeof(file_size));
	file_header_buf[OFFSET_TO_PIXEL_DATA] = HEADER_SIZE;
	write(fd, file_header_buf, FILE_HEADER_SIZE);
}


int		take_screenshot()
{
	int		fd;


	// draw_wolf(e);
	fd = open("bitmap.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

	write_file_header(fd);
	write_info_header(fd);
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