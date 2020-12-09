/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_background.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 13:50:14 by monoue            #+#    #+#             */
/*   Updated: 2020/11/30 16:38:23 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_background.h"

/*
** Projected wall height is calculated based on perpendicular distance from
** the player to wall.
**
** Our eyes are spherical, so distortion of view does not happen.
**
** In order to mimic the function, we have to calculate each projected wall
** height on the basis of the perpendicular distance instead of acutual
** distance.
**
** Unlike our natural view, the view in the screen is rectangle shaped.
**
** Therefore, we need to cut the cub3D world's view to "projection plane",
** which is based on the screen size of our PC.
**
** The field of view's edges are the edges of the window width.
**
** tan(FOV_ANGLE / 2) = (window_width / 2) / distance_proj_plane
**
** actual wall height(= TILE_SIZE) : projected wall height
** 					= actual distance to wall : distance to projected plane
*/

static int		calc_projected_wall_height(t_ray_to_wall ray)
{
	float perp_distance_to_wall;

	perp_distance_to_wall = ray.distance_to_wall
								* cos(ray.ray_angle - g_player.rotation_angle);
	return ((int)((g_distance_proj_plane / perp_distance_to_wall) * TILE_SIZE));
}

static void		render_ceiling_ray_basis(int window_x, int *window_y,
												const int projected_wall_height)
{
	int wall_top_pixel;

	wall_top_pixel = MAX((g_config.window_height / 2)
											- (projected_wall_height / 2), 0);
	g_color = g_config.ceiling_color;
	while (*window_y < wall_top_pixel)
	{
		draw_pixel(window_x, *window_y);
		(*window_y)++;
	}
}

static void		render_floor_ray_basis(int window_x, int window_y)
{
	g_color = g_config.floor_color;
	while (window_y < g_config.window_height)
	{
		draw_pixel(window_x, window_y);
		window_y++;
	}
}

static void		render_background_ray_basis(int window_x)
{
	int	projected_wall_height;
	int	window_y;

	projected_wall_height = calc_projected_wall_height(g_rays[window_x]);
	window_y = 0;
	render_ceiling_ray_basis(window_x, &window_y, projected_wall_height);
	render_wall_ray_basis(window_x, &window_y, projected_wall_height);
	render_floor_ray_basis(window_x, window_y);
}

void			render_background(void)
{
	int		window_x;

	window_x = 0;
	while (window_x < g_config.window_width)
	{
		render_background_ray_basis(window_x);
		window_x++;
	}
}
