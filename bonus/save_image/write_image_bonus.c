/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:16:16 by monoue            #+#    #+#             */
/*   Updated: 2020/12/01 12:19:09 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "write_image.h"

static int	calc_current_location_in_image_buf(int x, int y,
													const int image_size)
{
	const int line_size = g_config.window_width * 4;

	return (image_size - (line_size * (y + 1)) + x * 4);
}

static void	set_color_element(unsigned char *image_buf,
							const int current_location_in_buf,
							const int pixel_location,
							size_t color_element_index)
{
	const int	*addr = (const int *)g_img.addr;

	image_buf[current_location_in_buf + color_element_index] =
		(addr[pixel_location] >> (color_element_index * 8)) % ONE_BYTE_IN_DEC;
}

static void	set_current_pixel(unsigned char *image_buf, const int image_size,
																int x, int y)
{
	const int	pixel_location = (g_img.line_length / 4) * y + x;
	size_t		color_element_index;
	int			current_location_in_buf;

	current_location_in_buf = calc_current_location_in_image_buf(x, y,
																	image_size);
	color_element_index = 0;
	while (color_element_index < 4)
	{
		set_color_element(image_buf, current_location_in_buf, pixel_location,
														color_element_index);
		color_element_index++;
	}
}

void		write_image(int fd, const unsigned int image_size)
{
	int				y;
	int				x;
	unsigned char	image_buf[image_size];

	ft_bzero(image_buf, sizeof(image_buf));
	y = 0;
	while (y < g_config.window_height)
	{
		x = 0;
		while (x < g_config.window_width)
		{
			set_current_pixel(image_buf, image_size, x, y);
			x++;
		}
		y++;
	}
	write(fd, image_buf, image_size);
}
