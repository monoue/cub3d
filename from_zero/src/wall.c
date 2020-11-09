/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 13:50:14 by monoue            #+#    #+#             */
/*   Updated: 2020/11/09 16:57:19 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

/*
** Unlike our natural view, the view in the screen is rectangle shaped.
** Therefore, we need to cut the cub3D world's view to "projection plane".
** "distance_proj_plane" is how far the player is from the projection plane.
** The field of view's edges are the edges of the window width.
**
** tanjent (FOV_ANGLE / 2) = (window_width / 2) / distance_proj_plane
** actual height(= TILE_SIZE) : projected height = actual distance : distance_proj_plane
**
** perpendicular_distance is for fixing the "fishbowl effect".
** Our eyes are spherical, so distortion of view does not happen.
** In order to mimic the function, we have to calculate each projected wall height
** on the basis of the perpendicular distance instead of acutual distance.
** In order to get the color of each pixel from a texture,
** we can make use of the relation between the texture's width and
** TILE_SIZE.
** If we set these two to be the same, we can use wall_hit_vertical flag.
** If the horizontal face was hit, the column from which we should get
** each pixel's color is the same as the x coordinate of the hit
** divided by TILE_SIZE.
** Otherwise, the column is equal to the y coordinate divided by TILE_SIZE.
**
** In order to calculate the row from which we should get the color,
** we can make use of the ratio of TILE_SIZE : wall_strip_height.
**
** The solo difference between projected_wall_height and wall_strip_height
** is the object types of them.
**
** The reason we need the variable "distance_from_wall_strip_top" is to avoid the distortion
** which occurs when the wall_strip_height is longer than the window height.
*/

void	set_texture_color(t_texture texture, int x, int y)
{
	char	*pixel_color;

	pixel_color = texture.addr + (y * texture.line_length + x * (texture.bits_per_pixel / 8));
	g_color = *(unsigned int*)pixel_color;
}

void	render_wall_projection(void)
{
	int		window_x;
	float	distance_proj_plane;
	float	projected_wall_height;
	int		wall_strip_height;
	int		wall_top_pixel;
	int		wall_bottom_pixel;
	int		window_y;
	float	perpendicular_distance;

	window_x = 0;
	// while (r_i < NUM_RAYS)
	while (window_x < g_cubfile_data.window_width)
	{
		perpendicular_distance = rays[window_x].distance * cos(rays[window_x].ray_angle - g_player.rotation_angle);
		distance_proj_plane = (g_cubfile_data.window_width / 2) / tan(FOV_ANGLE / 2);
		// projected_wall_height = (TILE_SIZE / rays[r_i].distance) * distance_proj_plane;
		projected_wall_height = (TILE_SIZE / perpendicular_distance) * distance_proj_plane;

		// wall_strip_height と  projected_wall_height の違いは、int か float かだけ。
		wall_strip_height = (int)projected_wall_height;
		wall_top_pixel = (g_cubfile_data.window_height / 2) - (wall_strip_height / 2);
		if (wall_top_pixel < 0)
			wall_top_pixel = 0;
		wall_bottom_pixel = (g_cubfile_data.window_height / 2) + (wall_strip_height / 2);
		if (wall_bottom_pixel > g_cubfile_data.window_height)
			wall_bottom_pixel = g_cubfile_data.window_height;
		window_y = 0;
		g_color = g_cubfile_data.ceiling_color;
		while (window_y < wall_top_pixel)
		{
			draw_pixel(window_x, window_y);
			window_y++;
		}
		// if (rays[r_i].was_hit_vertical)
		// 	g_color = create_trgb(0, 255, 255, 255);
		// else
		// 	g_color = create_trgb(0, 220, 220, 220);
		// size_t	texture_offset_x;
		size_t	texture_offset_x;
		size_t	texture_offset_y;
		if (rays[window_x].was_hit_vertical)
			texture_offset_x = (size_t)rays[window_x].wall_hit_y % TILE_SIZE;
		else
			texture_offset_x = (size_t)rays[window_x].wall_hit_x % TILE_SIZE;
		// ここから追加中。英語コメントも後でまとめて付けるべき。
		t_texture texture;
		texture = g_textures[rays[window_x].direction];

		while (window_y < wall_bottom_pixel)
		{
			size_t distance_from_wall_strip_top = (window_y + (wall_strip_height / 2)) - (g_cubfile_data.window_height / 2);
			texture_offset_y = distance_from_wall_strip_top * ((float)TILE_SIZE / wall_strip_height);
			set_texture_color(texture, texture_offset_x, texture_offset_y);
			// これが縞々バージョン
			// g_color = wall_texture[(TILE_SIZE * texture_offset_y) + texture_offset_x];
			draw_pixel(window_x, window_y);
			window_y++;
		}
		g_color = g_cubfile_data.floor_color;
		while (window_y < g_cubfile_data.window_height)
		{
			draw_pixel(window_x, window_y);
			window_y++;
		}
		window_x++;
	}
}