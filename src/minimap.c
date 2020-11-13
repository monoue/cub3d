/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 13:43:16 by monoue            #+#    #+#             */
/*   Updated: 2020/11/13 13:45:28 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"

void	render_mini_map(void)
{
	size_t	y_i;
	size_t	x_i;
	size_t	tile_x;
	size_t	tile_y;

	y_i = 0;
	while (g_map[y_i][0] != '\0')
	{
		x_i = 0;
		while (g_map[y_i][x_i] != '\0')
		{
			tile_x = TILE_SIZE * x_i;
			tile_y = TILE_SIZE * y_i;
			if (g_map[y_i][x_i] == '1')
				g_color = create_trgb(0, 255, 255, 255);
			else if (g_map[y_i][x_i] == '2')
				g_color = create_trgb(0, 155, 155, 155);
			else
				g_color = create_trgb(0, 0, 0, 0);
			draw_rectangle(
				floor(tile_x * MINIMAP_SCALE_FACTOR),
				floor(tile_y * MINIMAP_SCALE_FACTOR),
				ceil(TILE_SIZE * MINIMAP_SCALE_FACTOR),
				ceil(TILE_SIZE * MINIMAP_SCALE_FACTOR)
			);
			x_i++;
		}
		y_i++;
	}
}