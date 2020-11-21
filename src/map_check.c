/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 13:56:12 by monoue            #+#    #+#             */
/*   Updated: 2020/11/21 16:37:00 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_check.h"

bool is_out_of_window(float x, float y)
{
	return (x < 0 || x >= MAX_MAP_LEN * TILE_SIZE || y < 0 || y >= MAX_MAP_LEN * TILE_SIZE);
}

bool	map_has_target_at(float x, float y, char c)
{
	int grid_x;
	int grid_y;

	grid_x = floor(x / TILE_SIZE);
	grid_y = floor(y / TILE_SIZE);
	if (grid_x < 0)
		grid_x = 0;
	if (grid_x > MAX_MAP_LEN)
		grid_x = MAX_MAP_LEN;
	if (grid_y < 0)
		grid_y = 0;
	if (grid_y > MAX_MAP_LEN)
		grid_y = MAX_MAP_LEN;
	return (g_map[grid_y][grid_x] == c);
}

bool	map_has_sprite_at(float x, float y)
{
	return (map_has_target_at(x, y, SPRITE_C));
}

bool	map_has_wall_at(float x, float y)
{
	return (map_has_target_at(x, y, WALL_C));
}

bool	is_space_at(const float pixel_x, const float pixel_y)
{
	int grid_x = floor(pixel_x / TILE_SIZE);
	int grid_y = floor(pixel_y / TILE_SIZE);

	if (is_out_of_window(pixel_x, pixel_y))
		return (false);
	if (grid_x < 0)
		grid_x = 0;
	if (grid_x > MAX_MAP_LEN)
		grid_x = MAX_MAP_LEN;
	if (grid_y < 0)
		grid_y = 0;
	if (grid_y > MAX_MAP_LEN)
		grid_y = MAX_MAP_LEN;
	return (g_map[grid_y][grid_x] == '1' ? false : true);
}