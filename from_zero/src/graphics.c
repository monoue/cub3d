/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:53:27 by monoue            #+#    #+#             */
/*   Updated: 2020/11/09 14:58:29 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

t_color	g_color;

void	draw_pixel(int x, int y)
{
    char    *dst;

    dst = g_img.addr + (y * g_img.line_length + x * (g_img.bits_per_pixel / 8));
    *(unsigned int*)dst = g_color;
}

void	draw_rectangle(size_t start_x, size_t start_y, size_t width, size_t height)
{
	size_t	y_i;
	size_t	x_i;

	y_i = 0;
	while (y_i < height)
	{
		x_i = 0;
		while (x_i < width)
		{
			draw_pixel(start_x + x_i, start_y + y_i);
			x_i++;
		}
		y_i++;
	}
}

static size_t	get_longer_side_length(int x0, int y0, int x1, int y1)
{
	int	delta_x;
	int	delta_y;

	delta_x = abs(x1 - x0);
	delta_y = abs(y1 - y0);
	return (MAX(delta_x, delta_y));
}

void	draw_line(int x0, int y0, int x1, int y1)
{
	size_t	longer_side_length;
	size_t	index;
	float	current_x;
	float	current_y;

	longer_side_length = get_longer_side_length(x0, y0, x1, y1);
	current_x = x0;
	current_y = y0;
	index = 0;
	while (index < longer_side_length)
	{
		draw_pixel(round(current_x), round(current_y));
		current_x += (x1 - x0) / (float)longer_side_length;
		current_y += (y1 - y0) / (float)longer_side_length;
		index++;
	}
}
