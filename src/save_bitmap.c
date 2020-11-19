/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bitmap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 09:19:48 by monoue            #+#    #+#             */
/*   Updated: 2020/11/19 15:08:01 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "save_bitmap.h"

void	ft_bdata(int fd)
{
	const int *addr = (const int *)g_img.addr;

	int				i;
	int				j;
	unsigned char	buffer[4];

	i = g_cubfile_data.window_width * (g_cubfile_data.window_height - 1);
	while (i >= 0)
	{
		j = 0;
		while (j < g_cubfile_data.window_width)
		{
			buffer[0] = (unsigned char)(addr[i] % 256);
			buffer[1] = (unsigned char)(addr[i] / 256 % 256);
			buffer[2] = (unsigned char)(addr[i] / 256 / 256 % 256);
			buffer[3] = (unsigned char)(addr[i] / 256 / 256 / 256);
			// buffer[3] = (unsigned char)(0);
			write(fd, buffer, 4);
			i++;
			j++;
		}
		i -= 2 * g_cubfile_data.window_width;
	}
}

// void	ft_bdata(int fd)
// {
// 	const int *addr = (const int *)g_img.addr;

// 	int				pixel_location;
// 	int				x;
// 	const int 
// 	unsigned char	image_buf[g_cubfile_data.window_height * g_cubfile_data.window_width * 4];

// 	pixel_location = g_cubfile_data.window_width * (g_cubfile_data.window_height - 1);
// 	while (pixel_location >= 0)
// 	{
// 		x = 0;
// 		while (x < g_cubfile_data.window_width)
// 		{
// 			image_buf[0] = (unsigned char)(addr[pixel_location] % 256);
// 			image_buf[1] = (unsigned char)(addr[pixel_location] / 256 % 256);
// 			image_buf[2] = (unsigned char)(addr[pixel_location] / 256 / 256 % 256);
// 			image_buf[3] = (unsigned char)(0);
// 			write(fd, image_buf, 4);
// 			pixel_location++;
// 			x++;
// 		}
// 		pixel_location -= 2 * g_cubfile_data.window_width;
// 	}

// 	int y = g_cubfile_data.window_height - 1;

// 	while (y >= 0)
// 	{
// 		x = 0;
// 		while (x < g_cubfile_data.window_width)
// 		{
// 			pixel_location = g_cubfile_data.window_width * y + x;
// 			// TODO: ビットシフトで書き直す
// 			image_buf[] = addr[pixel_location] % 256;
// 		}
// 	}
// 	// while (pixel_location >= 0)
// 	{
// 		x = 0;
// 		while (x < g_cubfile_data.window_width)
// 		{
// 			image_buf[0] = (unsigned char)(addr[pixel_location] % 256);
// 			image_buf[1] = (unsigned char)(addr[pixel_location] / 256 % 256);
// 			image_buf[2] = (unsigned char)(addr[pixel_location] / 256 / 256 % 256);
// 			image_buf[3] = (unsigned char)(0);
// 			write(fd, image_buf, 4);
// 			pixel_location++;
// 			x++;
// 		}
// 		pixel_location -= 2 * g_cubfile_data.window_width;
// 	}
// }

static void	set_file_header_data(unsigned char header_buf[HEADER_SIZE])
{
	// const int			real_width = g_cubfile_data.window_width * 3 + g_cubfile_data.window_width % 4;
	const int			real_width = g_cubfile_data.window_width * 4;
	const unsigned int	file_size = g_cubfile_data.window_height * real_width + HEADER_SIZE;

	header_buf[FILE_TYPE_1_OFFSET] = 'B';
	header_buf[FILE_TYPE_2_OFFSET] = 'M';
	ft_memcpy(&header_buf[FILE_SIZE_OFFSET], &file_size, sizeof(file_size));
	ft_memset(&header_buf[RESERVED_1_OFFSET], 0, 2);
	ft_memset(&header_buf[RESERVED_2_OFFSET], 0, 2);
	header_buf[OFFSET_TO_PIXEL_DATA_OFFSET] = HEADER_SIZE;
}

static void	set_info_header_data(unsigned char header_buf[HEADER_SIZE])
{
	// const int			real_width = g_cubfile_data.window_width * 3 + g_cubfile_data.window_width % 4;
	const int			real_width = g_cubfile_data.window_width * 4;
	const unsigned int	image_size = g_cubfile_data.window_height * real_width;

	header_buf[INFO_HEADER_SIZE_OFFSET] = INFO_HEADER_SIZE;
	ft_memcpy(&header_buf[IMAGE_WIDTH_OFFSET], &g_cubfile_data.window_width, sizeof(g_cubfile_data.window_width));
	ft_memcpy(&header_buf[IMAGE_HEIGHT_OFFSET], &g_cubfile_data.window_height, sizeof(g_cubfile_data.window_height));
	header_buf[PLANES_OFFSET] = PLANES;
	// header_buf[BITS_PER_PIXEL_OFFSET] = BITS_PER_PIXEL;
	header_buf[BITS_PER_PIXEL_OFFSET] = 32;
	ft_memset(&header_buf[COMPRESSION_METHOD_OFFSET], 0, 4);
	ft_memcpy(&header_buf[IMAGE_SIZE_OFFSET], &image_size, sizeof(image_size));
	ft_memset(&header_buf[HORZ_RESOLUTION_OFFSET], 0, 4);
	ft_memset(&header_buf[VERT_RESOLUTION_OFFSET], 0, 4);
	ft_memset(&header_buf[TOTAL_COLORS_OFFSET], 0, 4);
	ft_memset(&header_buf[IMPORTANT_COLORS_OFFSET], 0, 4);
}

int		take_screenshot()
{
	int				fd;
	unsigned char	header_buf[HEADER_SIZE];
	
	ft_bzero(header_buf, sizeof(header_buf));
	fd = open("bitmap.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	set_file_header_data(header_buf);
	set_info_header_data(header_buf);
	write(fd, header_buf, HEADER_SIZE);


	// draw_wolf(e);

	// write_file_header(fd);
	// write_info_header(fd);
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