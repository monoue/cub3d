/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 13:50:14 by monoue            #+#    #+#             */
/*   Updated: 2020/11/13 10:59:21 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wall.h"

/*
**
** In order to get the color of each pixel from a texture, we can make use of
** the relation between the texture's width and TILE_SIZE.
**
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
** The reason we need the variable "distance_from_wall_strip_top" is to avoid
** the distortion which occurs when the wall_strip_height is longer than
** the window height.
*/

void	set_texture_color(t_texture texture, int x, int y)
{
	char	*pixel_color;

	pixel_color = texture.addr + (y * texture.line_length + x * (texture.bits_per_pixel / 8));
	g_color = *(unsigned int*)pixel_color;
}

// TODO: ここの切り分けとコメント

// void	render_ceiling(int *window_y, )
// {
// 	const int wall_top_pixel = MAX((g_cubfile_data.window_height / 2) - (wall_strip_height / 2), 0);
// }


// distance_proj_plane -> projected_wall_height
// pependicular_distance -> projected_wall_height

/*
** Unlike our natural view, the view in the screen is rectangle shaped.
** Therefore, we need to cut the cub3D world's view to "projection plane".
** "distance_proj_plane" is how far the player is from the projection plane.
** The field of view's edges are the edges of the window width.
**
** tanjent (FOV_ANGLE / 2) = (window_width / 2) / distance_proj_plane
**
** actual height(= TILE_SIZE) : projected height
** 										= actual distance : distance_proj_plane
**
** Perpendicular_distance to wall is for fixing the "fishbowl effect".
** Our eyes are spherical, so distortion of view does not happen.
** In order to mimic the function, we have to calculate each projected wall
** height on the basis of the perpendicular distance instead of acutual
** distance.
*/
int		calc_projected_wall_height(int window_x)
{
	const float	distance_proj_plane
					= (g_cubfile_data.window_width / 2) / tan(FOV_ANGLE / 2);
	const float perp_distance_to_wall
		= g_rays[window_x].distance
				* cos(g_rays[window_x].ray_angle - g_player.rotation_angle);

	return ((int)(distance_proj_plane * (TILE_SIZE / perp_distance_to_wall)));
}

void	render_ceiling_ray_basis(int window_x, int *window_y, const int projected_wall_height)
{
	const int wall_top_pixel = MAX((g_cubfile_data.window_height / 2) - (projected_wall_height / 2), 0);

	g_color = g_cubfile_data.ceiling_color;
	while (*window_y < wall_top_pixel)
	{
		draw_pixel(window_x, *window_y);
		(*window_y)++;
	}

}

size_t	calc_texture_offset_x(t_ray_to_wall ray, float texture_width)
{
	const float texture_width_to_tile_size_ratio = texture_width / TILE_SIZE;
	const t_coord *wall_hit_coord = ray.wall_hit_coord;

	if (ray.was_hit_vertical)
		return (((size_t)wall_hit_coord->y % TILE_SIZE) * texture_width_to_tile_size_ratio);
	else
		return (((size_t)wall_hit_coord->x % TILE_SIZE) * texture_width_to_tile_size_ratio);
}

size_t	calc_texture_offset_y(int texture_height, const int projected_wall_height, int window_y)
{
	distance_from_wall_strip_top = (*window_y + (projected_wall_height / 2)) - (g_cubfile_data.window_height / 2);
	texture_offset_y = distance_from_wall_strip_top * ((float)texture.height / projected_wall_height);
}

void	render_wall_ray_basis(int window_x, int *window_y, const int projected_wall_height)
{
	size_t			texture_offset_y;
	size_t			distance_from_wall_strip_top;
	const int		wall_bottom_pixel = MIN((g_cubfile_data.window_height / 2) + (projected_wall_height / 2), g_cubfile_data.window_height);
	const t_texture texture = g_textures[g_rays[window_x].wall_hit_direction];
	const size_t	texture_offset_x = calc_texture_offset_x(g_rays[window_x], (float)texture.width);

	while (*window_y < wall_bottom_pixel)
	{
		distance_from_wall_strip_top = (*window_y + (projected_wall_height / 2)) - (g_cubfile_data.window_height / 2);
		texture_offset_y = distance_from_wall_strip_top * ((float)texture.height / projected_wall_height);
		texture_offset_y = calc_texture_offset_y(texture.height, projected_wall_height, *window_y);
		set_texture_color(texture, texture_offset_x, texture_offset_y);
		draw_pixel(window_x, *window_y);
		(*window_y)++;
	}
}

void	render_floor_ray_basis(int window_x, int window_y)
{
	g_color = g_cubfile_data.floor_color;
	while (window_y < g_cubfile_data.window_height)
	{
		draw_pixel(window_x, window_y);
		window_y++;
	}
}

void	render_background_ray_basis(int window_x)
{
	const int	projected_wall_height = calc_projected_wall_height(window_x);
	int			window_y;

	window_y = 0;
	render_ceiling_ray_basis(window_x, &window_y, projected_wall_height);
	render_wall_ray_basis(window_x, &window_y, projected_wall_height);
	render_floor_ray_basis(window_x, window_y);
}

void	render_background(void)
{
	int		window_x;

	window_x = 0;
	while (window_x < g_cubfile_data.window_width)
	{
		render_background_ray_basis(window_x);
		window_x++;
	}
}