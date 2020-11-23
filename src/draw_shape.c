/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shape.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 16:08:21 by monoue            #+#    #+#             */
/*   Updated: 2020/11/24 07:48:28 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_shape.h"

void			draw_rectangle(size_t start_x, size_t start_y, size_t width,
																size_t height)
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

void			draw_rectangle_minimap(size_t start_x, size_t start_y,
												size_t width, size_t height)
{
	draw_rectangle(
		floor(start_x * MINIMAP_SCALE_FACTOR),
		floor(start_y * MINIMAP_SCALE_FACTOR),
		ceil(width * MINIMAP_SCALE_FACTOR),
		ceil(height * MINIMAP_SCALE_FACTOR));
}

static size_t	get_longer_side_length(int x0, int y0, int x1, int y1)
{
	int	delta_x;
	int	delta_y;

	delta_x = abs(x1 - x0);
	delta_y = abs(y1 - y0);
	return (MAX(delta_x, delta_y));
}

void			draw_line(int x0, int y0, int x1, int y1)
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

void			draw_line_minimap(int x0, int y0, int x1, int y1)
{
	draw_line(
		x0 * MINIMAP_SCALE_FACTOR,
		y0 * MINIMAP_SCALE_FACTOR,
		x1 * MINIMAP_SCALE_FACTOR,
		y1 * MINIMAP_SCALE_FACTOR
	);
}
