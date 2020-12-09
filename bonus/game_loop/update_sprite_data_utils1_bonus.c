/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sprite_data_utils1_bonus.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 15:32:24 by monoue            #+#    #+#             */
/*   Updated: 2020/12/09 16:45:27 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "update_sprite_data_utils_bonus.h"

void	set_distance_from_player(size_t index)
{
	const float delta_x = g_sprites[index].x - g_player.x;
	const float delta_y = g_sprites[index].y - g_player.y;

	g_sprites[index].distance_from_player = sqrt(pow(delta_x, 2)
															+ pow(delta_y, 2));
}

void	set_angle_diff_from_player(size_t index)
{
	const float	x_difference = g_sprites[index].x - g_player.x;
	const float	y_difference = g_sprites[index].y - g_player.y;
	float		angle_from_player_to_sprite;
	float		angle_difference;

	angle_from_player_to_sprite = atan2f(y_difference, x_difference);
	angle_difference = g_player.rotation_angle - angle_from_player_to_sprite;
	if (angle_difference < -(PI))
		angle_difference += TWO_PI;
	if (angle_difference > PI)
		angle_difference -= TWO_PI;
	g_sprites[index].angle_diff_from_player = angle_difference;
}

void	set_perp_distance_from_player(size_t index)
{
	float	normalized_angle_diff;

	normalized_angle_diff = g_sprites[index].angle_diff_from_player;
	normalize_angle(&normalized_angle_diff);
	g_sprites[index].perp_distance_from_player = fabs(
		g_sprites[index].distance_from_player * cos(normalized_angle_diff));
}

void	set_projected_tile_size(size_t index)
{
	g_sprites[index].projected_tile_size = (int)
	((g_distance_proj_plane / g_sprites[index].perp_distance_from_player)
	* TILE_SIZE);
}
