/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 09:19:48 by monoue            #+#    #+#             */
/*   Updated: 2020/11/20 14:56:35 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "save_image.h"

int		calc_current_location_in_image_buf(int x, int y, const int image_buf_size)
{
	const int line_size = g_cubfile_data.window_width * 4;

	return (image_buf_size - (line_size * (y + 1)) + x * 4);
}

void	set_color_element(unsigned char *image_buf, const int current_location_in_buf, const int pixel_location, size_t color_element_index)
{
	const int	*addr = (const int *)g_img.addr;

	image_buf[current_location_in_buf + color_element_index] = (addr[pixel_location] >> (color_element_index * 8)) % (2 << 8);
}

void	set_current_pixel(unsigned char *image_buf, const int image_buf_size, int x, int y)
{
	const int	current_location_in_buf = calc_current_location_in_image_buf(x, y, image_buf_size);
	const int	pixel_location = g_cubfile_data.window_width * y + x;
	size_t		color_element_index;

	color_element_index = 0;
	while (color_element_index < 4)
	{
		set_color_element(image_buf, current_location_in_buf, pixel_location, color_element_index);
		color_element_index++;
	}
}

void	write_image(int fd)
{
	int				y;
	int				x;
	const int 		image_buf_size = g_cubfile_data.window_height * g_cubfile_data.window_width * 4 ;
	unsigned char	image_buf[image_buf_size];

	ft_bzero(image_buf, sizeof(image_buf));
	y = 0;
	while (y < g_cubfile_data.window_height)
	{
		x = 0;
		while (x < g_cubfile_data.window_width)
		{
			set_current_pixel(image_buf, image_buf_size, x, y);
			x++;
		}
		y++;
	}
	write(fd, image_buf, image_buf_size);
}

static void	set_file_header(unsigned char header_buf[HEADER_SIZE], const unsigned int image_size)
{
	const unsigned int	file_size = image_size + HEADER_SIZE;

	header_buf[FILE_TYPE_1_OFFSET] = 'B';
	header_buf[FILE_TYPE_2_OFFSET] = 'M';
	ft_memcpy(&header_buf[FILE_SIZE_OFFSET], &file_size, sizeof(file_size));
	ft_memset(&header_buf[RESERVED_1_OFFSET], 0, 2);
	ft_memset(&header_buf[RESERVED_2_OFFSET], 0, 2);
	header_buf[OFFSET_TO_PIXEL_DATA_OFFSET] = HEADER_SIZE;
}

static void	set_info_header(unsigned char header_buf[HEADER_SIZE], const unsigned int image_size)
{
	header_buf[INFO_HEADER_SIZE_OFFSET] = INFO_HEADER_SIZE;
	ft_memcpy(&header_buf[IMAGE_WIDTH_OFFSET], &g_cubfile_data.window_width, sizeof(g_cubfile_data.window_width));
	ft_memcpy(&header_buf[IMAGE_HEIGHT_OFFSET], &g_cubfile_data.window_height, sizeof(g_cubfile_data.window_height));
	header_buf[PLANES_OFFSET] = PLANES;
	header_buf[BITS_PER_PIXEL_OFFSET] = g_img.bits_per_pixel;
	ft_memset(&header_buf[COMPRESSION_METHOD_OFFSET], 0, 4);
	ft_memcpy(&header_buf[IMAGE_SIZE_OFFSET], &image_size, sizeof(image_size));
	ft_memset(&header_buf[HORZ_RESOLUTION_OFFSET], 0, 4);
	ft_memset(&header_buf[VERT_RESOLUTION_OFFSET], 0, 4);
	ft_memset(&header_buf[TOTAL_COLORS_OFFSET], 0, 4);
	ft_memset(&header_buf[IMPORTANT_COLORS_OFFSET], 0, 4);
}

void	write_header(int fd)
{
	unsigned char		header_buf[HEADER_SIZE];
	const int			line_size = g_cubfile_data.window_width * 4;
	const unsigned int	image_size = g_cubfile_data.window_height * line_size;

	ft_bzero(header_buf, sizeof(header_buf));
	set_file_header(header_buf, image_size);
	set_info_header(header_buf, image_size);
	write(fd, header_buf, HEADER_SIZE);
}

void	write_bmp_file()
{
	int	fd;

	fd = open("bitmap.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	write_header(fd);
	write_image(fd);
	close(fd);
}

void	save_image()
{
	write_bmp_file();
	write(1, "Screenshot saved!\n", 18);
	exit(1);
}