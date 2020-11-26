/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sprite_data_utils2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 15:34:12 by monoue            #+#    #+#             */
/*   Updated: 2020/11/26 15:36:43 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "update_sprite_data_utils.h"

static int	calc_sprite_center_x(size_t index)
{
	float	window_center_and_sprite_x_diff;

	window_center_and_sprite_x_diff = (g_cubfile_data.window_width
						/ FOV_ANGLE) * g_sprites[index].angle_diff_from_player;
	return (g_cubfile_data.window_width / 2
			- (window_center_and_sprite_x_diff));
}

static int	calc_projection_left_edge(size_t index)
{
	int		sprite_center_x;

	sprite_center_x = calc_sprite_center_x(index);
	return (sprite_center_x - g_sprites[index].projected_tile_size / 2);
}

void		set_projection_edges(size_t index)
{
	const int projected_tile_size = g_sprites[index].projected_tile_size;
	const int window_height = g_cubfile_data.window_height;
	const int projection_left_edge = calc_projection_left_edge(index);
	const int projection_top = (window_height / 2) - (projected_tile_size / 2);

	g_sprites[index].projection_left_edge = projection_left_edge;
	g_sprites[index].projection_right_edge = projection_left_edge
												+ projected_tile_size;
	g_sprites[index].projection_top = projection_top;
	g_sprites[index].projection_bottom = projection_top + projected_tile_size;
}
