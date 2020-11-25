/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_ray_basis.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 17:43:22 by monoue            #+#    #+#             */
/*   Updated: 2020/11/25 09:53:08 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_wall_ray_basis.h"

static size_t	calc_texture_offset_x(t_ray_to_wall ray, float texture_width)
{
	const t_coord	*wall_hit_coord = ray.wall_hit_coord;
	float			texture_width_to_tile_size_ratio;

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

/*
** In order to calculate the row from which we should get the color,
** we can make use of the ratio of texture_height : projected_wall_height.
**
** The reason we need the variable "distance_from_wall_strip_top" is to avoid
** the distortion which occurs when the wall_strip_height is longer than
** the window height.
*/

static size_t	calc_texture_offset_y(int texture_height,
								const int projected_wall_height, int window_y)
{
	size_t distance_from_wall_strip_top;

	distance_from_wall_strip_top = (window_y
									+ (projected_wall_height / 2))
									- (g_cubfile_data.window_height / 2);
	return (distance_from_wall_strip_top
							* ((float)texture_height / projected_wall_height));
}

void			set_texture_color(t_texture texture, int x, int y)
{
	char	*pixel_color;

	pixel_color = texture.addr
				+ (y * texture.line_length + x * (texture.bits_per_pixel / 8));
	g_color = *(unsigned int*)pixel_color;
}

void			render_wall_ray_basis(int window_x, int *window_y,
												const int projected_wall_height)
{
	size_t			texture_offset_y;
	const t_texture texture = g_textures[g_rays[window_x].wall_hit_direction];
	int				wall_bottom_pixel;
	size_t			texture_offset_x;

	wall_bottom_pixel = MIN((g_cubfile_data.window_height / 2)
				+ (projected_wall_height / 2), g_cubfile_data.window_height);
	texture_offset_x = calc_texture_offset_x(g_rays[window_x],
														(float)texture.width);
	while (*window_y < wall_bottom_pixel)
	{
		texture_offset_y = calc_texture_offset_y(texture.height,
													projected_wall_height,
													*window_y);
		set_texture_color(texture, texture_offset_x, texture_offset_y);
		draw_pixel(window_x, *window_y);
		(*window_y)++;
	}
}
