/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 23:21:28 by monoue            #+#    #+#             */
/*   Updated: 2020/11/25 15:51:57 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_sprites.h"

float	calc_player_and_sprite_angle_diff(size_t index)
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
	return (angle_difference);
}

int		calc_projected_sprite_tile_size(size_t	index)
{
	float	perp_distance_to_sprite;
	float	normalized_angle_difference;

	normalized_angle_difference
					= calc_player_and_sprite_angle_diff(index);
	normalize_angle(&normalized_angle_difference);
	perp_distance_to_sprite = fabs(g_sprites[index].distance_from_player
										* cos(normalized_angle_difference));
	return ((int)(TILE_SIZE
					* (g_distance_proj_plane / perp_distance_to_sprite)));
}


size_t	calc_sprite_texture_offset_x(t_ray_to_wall ray, float texture_width)
{
	float			texture_width_to_tile_size_ratio;
	const t_coord	*wall_hit_coord = ray.wall_hit_coord;

	texture_width_to_tile_size_ratio = texture_width / TILE_SIZE;
	if (ray.was_hit_vertical)
	{
		return (((size_t)wall_hit_coord->y % TILE_SIZE)
											* texture_width_to_tile_size_ratio);
	}
	else
	{
		return (((size_t)wall_hit_coord->x % TILE_SIZE)
											* texture_width_to_tile_size_ratio);
	}
}

size_t	calc_sprite_texture_offset_y(int texture_height,
								const int projected_wall_height, int window_y)
{
	size_t distance_from_wall_strip_top;

	distance_from_wall_strip_top = (window_y + (projected_wall_height / 2))
									- (g_cubfile_data.window_height / 2);
	return (distance_from_wall_strip_top *
							((float)texture_height / projected_wall_height));
}

int			calc_sprite_center_x(float player_and_sprite_angle_diff)
{
	float	window_center_and_sprite_x_diff;

	window_center_and_sprite_x_diff = (g_cubfile_data.window_width
									/ FOV_ANGLE) * player_and_sprite_angle_diff;
	return (g_cubfile_data.window_width / 2 - (window_center_and_sprite_x_diff));
}

float	calc_perp_distance_to_sprite(size_t index,
											float player_and_sprite_angle_diff)
{
	float	normalized_angle_diff;

	normalized_angle_diff = player_and_sprite_angle_diff;
	normalize_angle(&normalized_angle_diff);
	return (fabs(g_sprites[index].distance_from_player
												* cos(normalized_angle_diff)));
}
// norm trying

// TODO: 関数作るまでもないかも？ x に計算して入れてやればいいだけだ。
// いや、ストップの部分（下端と右端）はちゃんと固定値に決めてやらなきゃいけない。
int		calc_sprite_left_edge(float player_and_sprite_angle_diff, int projected_sprite_tile_size)
{
	int		sprite_center_x;

	sprite_center_x = calc_sprite_center_x(player_and_sprite_angle_diff);
	return (sprite_center_x - projected_sprite_tile_size / 2);
}

static void	render_sprite(size_t index)
{
	float	player_and_sprite_angle_diff;

	player_and_sprite_angle_diff = calc_player_and_sprite_angle_diff(index);
	if (player_and_sprite_angle_diff >= FOV_ANGLE
		|| player_and_sprite_angle_diff <= -(FOV_ANGLE))
	{
		return ;
	}
	float perp_distance_to_sprite = calc_perp_distance_to_sprite(index, player_and_sprite_angle_diff);
	int		projected_sprite_tile_size = calc_projected_sprite_tile_size(index);

	// projected_sprite_tile_size の正方形なのだから、以下は高さと幅に分ける必要はない。かなりきれいにまとめられるはず。
	const int assumed_sprite_top = (g_cubfile_data.window_height / 2) - (projected_sprite_tile_size / 2);
	const int sprite_top = MAX(assumed_sprite_top, 0);
	const int	assumed_sprite_bottom_pixel = assumed_sprite_top + projected_sprite_tile_size;
	const int		sprite_bottom = MIN(assumed_sprite_bottom_pixel, g_cubfile_data.window_height);
	const int sprite_height = assumed_sprite_bottom_pixel - assumed_sprite_top;
	// const int		sprite_left_edge_pixel = sprite_center_x - projected_sprite_tile_size / 2;
	// const int		sprite_right_edge_pixel = MIN(sprite_left_edge_pixel + projected_sprite_tile_size, g_cubfile_data.window_width);
	// int x = sprite_left_edge_pixel;
	int sprite_left_edge = calc_sprite_left_edge(player_and_sprite_angle_diff, projected_sprite_tile_size);
	int x = sprite_left_edge;
	const int		sprite_right_edge = MIN(x + projected_sprite_tile_size, g_cubfile_data.window_width);
	while (x < sprite_right_edge)
	{
		if (x < 0 || g_rays[x].distance_to_wall <= perp_distance_to_sprite)
			;
		else
		{
			// int sprite_texture_offset_x = (int)((float)(x - sprite_left_edge_pixel) / sprite_width * g_textures[SPRITE].width);
			int sprite_texture_offset_x = (int)((float)(x - sprite_left_edge) / projected_sprite_tile_size * g_textures[SPRITE].width);

			int y = sprite_top;
			while (y < sprite_bottom)
			{
				int sprite_texture_offset_y = (int)((float)(y - sprite_top) / sprite_height * g_textures[SPRITE].height);
				set_texture_color(g_textures[SPRITE], sprite_texture_offset_x, sprite_texture_offset_y);
				if (g_color)
					draw_pixel(x, y);
				y++;
			}
		}
		x++;
	}
}


void	render_sprites(void)
{
	size_t	index;

	index = 0;
	while (index < g_cubfile_data.sprites_num)
	{
		render_sprite(index);
		index++;
	}
}

// 動くオリジナル
// static void	render_sprite(size_t index)
// {
// 	const float	angle_difference_between_player_and_sprite = calc_angle_difference_between_player_and_sprite(index);
// 	if (angle_difference_between_player_and_sprite >= FOV_ANGLE || angle_difference_between_player_and_sprite <= -(FOV_ANGLE))
// 		return ;
// 	float	x_difference_between_window_center_and_sprite = (g_cubfile_data.window_width / FOV_ANGLE)
// 		* angle_difference_between_player_and_sprite;
// 	int		sprite_center_x = g_cubfile_data.window_width / 2 - (x_difference_between_window_center_and_sprite);

// 	float	normalized_angle_difference = calc_angle_difference_between_player_and_sprite(index);
// 	normalize_angle(&normalized_angle_difference);
// 	const float perp_distance_to_project
// 	= fabs(g_sprites[index].distance_from_player * cos(normalized_angle_difference));
// 	int		projected_sprite_tile_size = calc_projected_sprite_tile_size(index);

// 	// 正方形なのだから、以下は高さと幅に分ける必要はない。かなりきれいにまとめられるはず。
// 	const int assumed_sprite_top_pixel = (g_cubfile_data.window_height / 2) - (projected_sprite_tile_size / 2);
// 	const int sprite_top_pixel = MAX((g_cubfile_data.window_height / 2) - (projected_sprite_tile_size / 2), 0);
// 	const int		assumed_sprite_bottom_pixel = (g_cubfile_data.window_height / 2) + (projected_sprite_tile_size / 2);
// 	const int		sprite_bottom_pixel = MIN((g_cubfile_data.window_height / 2) + (projected_sprite_tile_size / 2), g_cubfile_data.window_height);
// 	const int sprite_height = assumed_sprite_bottom_pixel - assumed_sprite_top_pixel;
// 	const int		sprite_left_edge_pixel = sprite_center_x - projected_sprite_tile_size / 2;
// 	const int		sprite_right_edge_pixel = MIN(sprite_center_x + projected_sprite_tile_size / 2, g_cubfile_data.window_width);
// 	const int sprite_width = sprite_height;
// 	int x = sprite_left_edge_pixel;
// 	// とりあえずテストのため、二重に書いている。あとでまとめる
// 	// ここまで、ダブっている
// 	while (x < sprite_right_edge_pixel)
// 	{
// 		if (x < 0 || g_rays[x].distance_to_wall <= perp_distance_to_project)
// 			;
// 		else
// 		{
// 			int sprite_texture_offset_x = (int)((float)(x - sprite_left_edge_pixel) / sprite_width * g_textures[SPRITE].width);

// 			int y = sprite_top_pixel;
// 			while (y < sprite_bottom_pixel)
// 			{
// 				int sprite_texture_offset_y = (int)((float)(y - sprite_top_pixel) / sprite_height * g_textures[SPRITE].height);
// 				set_texture_color(g_textures[SPRITE], sprite_texture_offset_x, sprite_texture_offset_y);
// 				if (g_color)
// 					draw_pixel(x, y);
// 				y++;
// 			}
// 		}
// 		x++;
// 	}
// }