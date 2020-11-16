/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mini_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 13:43:16 by monoue            #+#    #+#             */
/*   Updated: 2020/11/16 14:31:04 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_mini_map.h"

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

void	render_rays(void)
{
	size_t	index;

	index = 0;
	g_color = create_trgb(245, 255, 241, 0);
	while (index < (size_t)g_cubfile_data.window_width)
	{
		draw_line
		(
			g_player.x * MINIMAP_SCALE_FACTOR,
			g_player.y * MINIMAP_SCALE_FACTOR,
			g_rays[index].wall_hit_coord->x * MINIMAP_SCALE_FACTOR,
			g_rays[index].wall_hit_coord->y * MINIMAP_SCALE_FACTOR
		);
		index++;
	}
	// test_ray_data(0);
	// test_ray_data(NUM_RAYS - 1);
}

void	render_player(void)
{
	g_color = create_trgb(0, 0, 255, 255);
	draw_rectangle(
		g_player.x * MINIMAP_SCALE_FACTOR,
		g_player.y * MINIMAP_SCALE_FACTOR,
		g_player.width * MINIMAP_SCALE_FACTOR, g_player.height * MINIMAP_SCALE_FACTOR
	);
	draw_line(
		g_player.x * MINIMAP_SCALE_FACTOR,
		g_player.y * MINIMAP_SCALE_FACTOR,
		(g_player.x + cos(g_player.rotation_angle) * 40) * MINIMAP_SCALE_FACTOR,
		(g_player.y + sin(g_player.rotation_angle) * 40) * MINIMAP_SCALE_FACTOR
	);
}

void	render_rays_to_sprites()
{
	size_t			index;
	const size_t	s_num = g_cubfile_data.sprites_num;

	index = 0;
	while (index < s_num)
	{
		g_color = create_trgb(230, floor(255 * index / (s_num - 1)), 50, floor(255 - 255 * (index / (s_num - 1))));
		draw_line(
			g_player.x * MINIMAP_SCALE_FACTOR,
			g_player.y * MINIMAP_SCALE_FACTOR,
			g_sprites[index].x * MINIMAP_SCALE_FACTOR,
			g_sprites[index].y * MINIMAP_SCALE_FACTOR);
		index++;
	}
}