/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 23:21:28 by monoue            #+#    #+#             */
/*   Updated: 2020/11/24 08:56:18 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_sprites.h"

float	calc_angle_difference_between_player_and_sprite(size_t index)
{
	const float	x_difference = g_sprites[index].x - g_player.x;
	const float	y_difference = g_sprites[index].y - g_player.y;
	const float	angle_from_player_to_sprite = atan2f(y_difference,
																x_difference);
	float		angle_difference;

	angle_difference = g_player.rotation_angle - angle_from_player_to_sprite;
    if (angle_difference < -(PI))
        angle_difference += TWO_PI;
    if (angle_difference > PI)
        angle_difference -= TWO_PI;
	return (angle_difference);
}

void	render_from_top_to_sprite_ray_basis(int window_x, int *window_y,
											const int projected_sprite_height)
{
	const int sprite_top_pixel
		= MAX((g_cubfile_data.window_height / 2)
				- (projected_sprite_height / 2),
				0);

	g_color = create_trgb(0, 0, 255, 0);
	while (*window_y < sprite_top_pixel)
	{
		draw_pixel(window_x, *window_y);
		(*window_y)++;
	}
}

int		calc_projected_sprite_height(size_t	index)
{
	float	perp_distance_to_project;
	float	normalized_angle_difference;

	normalized_angle_difference
					= calc_angle_difference_between_player_and_sprite(index);
	normalize_angle(&normalized_angle_difference);
	perp_distance_to_project = fabs(g_sprites[index].distance_from_player
										* cos(normalized_angle_difference));
	return ((int)(TILE_SIZE
			* (g_distance_proj_plane / perp_distance_to_project)));
}

size_t	calc_sprite_texture_offset_x(t_ray_to_wall ray, float texture_width)
{
	const float		texture_width_to_tile_size_ratio
												= texture_width / TILE_SIZE;
	const t_coord	*wall_hit_coord = ray.wall_hit_coord;

	if (ray.was_hit_vertical)
		return (((size_t)wall_hit_coord->y % TILE_SIZE)
											* texture_width_to_tile_size_ratio);
	else
		return (((size_t)wall_hit_coord->x % TILE_SIZE)
											* texture_width_to_tile_size_ratio);
}

size_t	calc_sprite_texture_offset_y(int texture_height,
								const int projected_wall_height, int window_y)
{
	const size_t distance_from_wall_strip_top =
									(window_y + (projected_wall_height / 2))
									- (g_cubfile_data.window_height / 2);

	return (distance_from_wall_strip_top *
							((float)texture_height / projected_wall_height));
}

static void	render_sprite(size_t index)
{
	const float	angle_difference_between_player_and_sprite = calc_angle_difference_between_player_and_sprite(index);
	if (angle_difference_between_player_and_sprite >= FOV_ANGLE || angle_difference_between_player_and_sprite <= -(FOV_ANGLE))
		return ;
	float	x_difference_between_window_center_and_sprite = (g_cubfile_data.window_width / FOV_ANGLE)
		* angle_difference_between_player_and_sprite;
	int		sprite_center_x = g_cubfile_data.window_width / 2 - (x_difference_between_window_center_and_sprite);

	float	normalized_angle_difference = calc_angle_difference_between_player_and_sprite(index);
	normalize_angle(&normalized_angle_difference);
	const float perp_distance_to_project
	= fabs(g_sprites[index].distance_from_player * cos(normalized_angle_difference));
	int		projected_sprite_tile_size = calc_projected_sprite_height(index);

	// 正方形なのだから、以下は高さと幅に分ける必要はない。かなりきれいにまとめられるはず。
	const int assumed_sprite_top_pixel = (g_cubfile_data.window_height / 2) - (projected_sprite_tile_size / 2);
	const int sprite_top_pixel = MAX((g_cubfile_data.window_height / 2) - (projected_sprite_tile_size / 2), 0);
	const int		assumed_sprite_bottom_pixel = (g_cubfile_data.window_height / 2) + (projected_sprite_tile_size / 2);
	const int		sprite_bottom_pixel = MIN((g_cubfile_data.window_height / 2) + (projected_sprite_tile_size / 2), g_cubfile_data.window_height);
	const int sprite_height = assumed_sprite_bottom_pixel - assumed_sprite_top_pixel;
	const int		sprite_left_edge_pixel = sprite_center_x - projected_sprite_tile_size / 2;
	const int		sprite_right_edge_pixel = MIN(sprite_center_x + projected_sprite_tile_size / 2, g_cubfile_data.window_width);
	const int sprite_width = sprite_height;
	int x = sprite_left_edge_pixel;
	// とりあえずテストのため、二重に書いている。あとでまとめる
	// ここまで、ダブっている
	while (x < sprite_right_edge_pixel)
	{
		if (x < 0 || g_rays[x].distance_to_wall <= perp_distance_to_project)
			;
		else
		{
			int sprite_texture_offset_x = (int)((float)(x - sprite_left_edge_pixel) / sprite_width * g_textures[SPRITE].width);

			int y = sprite_top_pixel;
			while (y < sprite_bottom_pixel)
			{
				int sprite_texture_offset_y = (int)((float)(y - sprite_top_pixel) / sprite_height * g_textures[SPRITE].height);
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