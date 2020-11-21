/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mini_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 13:43:16 by monoue            #+#    #+#             */
/*   Updated: 2020/11/21 16:05:51 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_mini_map.h"

void	render_grid(void)
{
	size_t	y_i;
	size_t	x_i;

	y_i = 0;
	while (g_map[y_i][0] != '\0')
	{
		x_i = 0;
		while (g_map[y_i][x_i] != '\0')
		{
			if (g_map[y_i][x_i] == WALL_C)
				g_color = create_trgb(0, 255, 255, 255);
			else if (g_map[y_i][x_i] == SPRITE_C)
				g_color = create_trgb(0, 155, 155, 155);
			else
				g_color = create_trgb(0, 0, 0, 0);
			draw_rectangle_minimap(
				x_i * TILE_SIZE,
				y_i * TILE_SIZE,
				TILE_SIZE,
				TILE_SIZE
			);
			x_i++;
		}
		y_i++;
	}
}

void	render_rays_to_wall(void)
{
	size_t	index;

	index = 0;
	g_color = create_trgb(0, 255, 241, 0);
	draw_line_minimap
	(g_player.x, g_player.y, g_rays[0].wall_hit_coord->x, g_rays[0].wall_hit_coord->y);
	draw_line_minimap
	(
		g_player.x,
		g_player.y,
		g_rays[g_cubfile_data.window_width - 1].wall_hit_coord->x,
		g_rays[g_cubfile_data.window_width - 1].wall_hit_coord->y
	);
}

void	render_player(void)
{
	g_color = create_trgb(0, 0, 255, 255);
	draw_rectangle_minimap(g_player.x, g_player.y, g_player.width, g_player.height);
	draw_line_minimap(
		g_player.x,
		g_player.y,
		(g_player.x + cos(g_player.rotation_angle) * 500),
		(g_player.y + sin(g_player.rotation_angle) * 500)
	);
}

void	render_lines_to_sprites_center()
{
	size_t			index;
	const size_t	s_num = g_cubfile_data.sprites_num;

	if (g_cubfile_data.sprites_num == 0)
		;
	else if (g_cubfile_data.sprites_num == 1)
	{
		g_color = create_trgb(0, 255, 0, 0);
		draw_line_minimap(g_player.x, g_player.y, g_sprites[0].x, g_sprites[0].y);
	}
	else
	{
		index = 0;
		while (index < s_num)
		{
			g_color = create_trgb(0, floor(255 * index / (s_num - 1)), 50, floor(255 - 255 * (index / (s_num - 1))));
			draw_line_minimap(g_player.x, g_player.y, g_sprites[index].x,g_sprites[index].y);
			index++;
		}
	}
}
void	render_mini_map(void)
{
	render_grid();
	render_rays_to_wall();
	render_lines_to_sprites_center();
	render_player();
}

