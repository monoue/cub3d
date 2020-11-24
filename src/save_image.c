/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:12:59 by monoue            #+#    #+#             */
/*   Updated: 2020/11/24 13:17:02 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "save_image.h"


static void	set_file_header(unsigned char header_buf[HEADER_SIZE],
												const unsigned int image_size)
{
	const unsigned int	file_size = image_size + HEADER_SIZE;

	header_buf[FILE_TYPE_1_OFFSET] = 'B';
	header_buf[FILE_TYPE_2_OFFSET] = 'M';
	ft_memcpy(&header_buf[FILE_SIZE_OFFSET], &file_size, sizeof(file_size));
	ft_memset(&header_buf[RESERVED_1_OFFSET], 0, 2);
	ft_memset(&header_buf[RESERVED_2_OFFSET], 0, 2);
	header_buf[OFFSET_TO_PIXEL_DATA_OFFSET] = HEADER_SIZE;
}

static void	set_info_header(unsigned char header_buf[HEADER_SIZE],
												const unsigned int image_size)
{
	header_buf[INFO_HEADER_SIZE_OFFSET] = INFO_HEADER_SIZE;
	ft_memcpy(&header_buf[IMAGE_WIDTH_OFFSET], &g_cubfile_data.window_width,
										sizeof(g_cubfile_data.window_width));
	ft_memcpy(&header_buf[IMAGE_HEIGHT_OFFSET], &g_cubfile_data.window_height,
										sizeof(g_cubfile_data.window_height));
	header_buf[PLANES_OFFSET] = PLANES;
	header_buf[BITS_PER_PIXEL_OFFSET] = g_img.bits_per_pixel;
	ft_memset(&header_buf[COMPRESSION_METHOD_OFFSET], 0, 4);
	ft_memcpy(&header_buf[IMAGE_SIZE_OFFSET], &image_size, sizeof(image_size));
	ft_memset(&header_buf[HORZ_RESOLUTION_OFFSET], 0, 4);
	ft_memset(&header_buf[VERT_RESOLUTION_OFFSET], 0, 4);
	ft_memset(&header_buf[TOTAL_COLORS_OFFSET], 0, 4);
	ft_memset(&header_buf[IMPORTANT_COLORS_OFFSET], 0, 4);
}

// write_bmp_file
void	write_header(int fd, const unsigned int image_size)
{
	unsigned char	header_buf[HEADER_SIZE];

	ft_bzero(header_buf, sizeof(header_buf));
	set_file_header(header_buf, image_size);
	set_info_header(header_buf, image_size);
	write(fd, header_buf, HEADER_SIZE);
}

// save_image
void	write_bmp_file()
{
	const int			line_size = g_cubfile_data.window_width * 4;
	const unsigned int	image_size = g_cubfile_data.window_height * line_size;
	int	fd;

	fd = open("bitmap.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	write_header(fd, image_size);
	write_image(fd, image_size);
	close(fd);
}

void	save_image()
{
	write_bmp_file();
	write(1, "Screenshot saved!\n", 18);
	exit(1);
}