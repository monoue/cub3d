/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 23:21:28 by monoue            #+#    #+#             */
/*   Updated: 2020/11/27 10:44:02 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_sprites.h"

static int	calc_texture_x(size_t index, int window_x)
{
	return ((int)((float)(window_x - g_sprites[index].projection_left_edge)
			/ g_sprites[index].projected_tile_size * g_textures[SPRITE].width));
}

static int	calc_texture_y(size_t index, int window_y)
{
	return ((int)((float)(window_y - g_sprites[index].projection_top)
		/ g_sprites[index].projected_tile_size * g_textures[SPRITE].height));
}

static void	draw_sprite_vertical_line(size_t index, int window_x)
{
	const int	texture_x = calc_texture_x(index, window_x);
	int			window_y;
	int			window_y_end;
	int			texture_y;

	window_y = MAX(g_sprites[index].projection_top, 0);
	window_y_end = MIN(g_sprites[index].projection_bottom,
						g_cubfile_data.window_height);
	while (window_y < window_y_end)
	{
		texture_y = calc_texture_y(index, window_y);
		set_texture_color(g_textures[SPRITE], texture_x, texture_y);
		if (g_color)
			draw_pixel(window_x, window_y);
		window_y++;
	}
}

static void	render_sprite(size_t index)
{
	int x;
	int x_end;

	if (g_sprites[index].angle_diff_from_player >= FOV_ANGLE
		|| g_sprites[index].angle_diff_from_player <= -(FOV_ANGLE))
	{
		return ;
	}
	x = MAX(g_sprites[index].projection_left_edge, 0);
	x_end = MIN(g_sprites[index].projection_right_edge,
				g_cubfile_data.window_width);
	while (x < x_end)
	{
		if (g_rays[x].distance_to_wall
			<= g_sprites[index].perp_distance_from_player)
			;
		else
			draw_sprite_vertical_line(index, x);
		x++;
	}
}

void		render_sprites(void)
{
	size_t	index;

	index = 0;
	while (index < g_cubfile_data.sprites_num)
	{
		render_sprite(index);
		index++;
	}
}
