/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sprites_data.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 12:04:28 by monoue            #+#    #+#             */
/*   Updated: 2020/11/26 15:12:19 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "update_sprites_data.h"

static void	set_distance_from_player(size_t index)
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

void	set_projected_tile_size(size_t	index)
{
	g_sprites[index].projected_tile_size = (int)(TILE_SIZE
		* (g_distance_proj_plane / g_sprites[index].perp_distance_from_player));
}
static int	calc_sprite_center_x(size_t index)
{
	float	window_center_and_sprite_x_diff;

	window_center_and_sprite_x_diff = (g_cubfile_data.window_width
						/ FOV_ANGLE) * g_sprites[index].angle_diff_from_player;
	return (g_cubfile_data.window_width / 2 - (window_center_and_sprite_x_diff));
}

int	calc_projection_left_edge(size_t index)
{
	int		sprite_center_x;

	sprite_center_x = calc_sprite_center_x(index);
	return (sprite_center_x - g_sprites[index].projected_tile_size / 2);
}

void	set_projection_edges(index)
{
	const int	projected_tile_size = g_sprites[index].projected_tile_size;
	const int	window_height = g_cubfile_data.window_height;
	const int	projection_left_edge = calc_projection_left_edge(index);
	const int	projection_top = (window_height / 2) - (projected_tile_size / 2);

	g_sprites[index].projection_left_edge = projection_left_edge;
	g_sprites[index].projection_right_edge = projection_left_edge + projected_tile_size;
	g_sprites[index].projection_top = projection_top;
	g_sprites[index].projection_bottom = projection_top + projected_tile_size;
}

static void	update_sprite_data(size_t index)
{
	set_distance_from_player(index);
	set_angle_diff_from_player(index);
	set_perp_distance_from_player(index);
	set_projected_tile_size(index);
	set_projection_edges(index);
}

static void	update_all_sprites_data(void)
{
	size_t	index;

	index = 0;
	while (index < g_cubfile_data.sprites_num)
	{
		update_sprite_data(index);
		index++;
	}
}

static void	sort_sprites(void)
{
	size_t		index;
	size_t		inner_i;
	t_sprite	tmp;

	index = 0;
	while (index < g_cubfile_data.sprites_num - 1)
	{
		inner_i = index + 1;
		while (inner_i < g_cubfile_data.sprites_num)
		{
			if (g_sprites[index].distance_from_player
									< g_sprites[inner_i].distance_from_player)
			{
				tmp = g_sprites[index];
				g_sprites[index] = g_sprites[inner_i];
				g_sprites[inner_i] = tmp;
			}
			inner_i++;
		}
		index++;
	}
}

void		update_and_sort_sprites_data(void)
{
	update_all_sprites_data();
	sort_sprites();
}
