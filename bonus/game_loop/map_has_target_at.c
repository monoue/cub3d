/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_has_target_at.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 13:56:12 by monoue            #+#    #+#             */
/*   Updated: 2020/11/27 15:48:08 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_has_target_at.h"

static bool	map_has_target_at(float x, float y, char target)
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
	return (g_map[grid_y][grid_x] == target);
}

static bool	map_has_object_at(float x, float y)
{
	return (map_has_target_at(x, y, SPRITE_C));
}

bool		map_has_wall_at(float x, float y)
{
	return (map_has_target_at(x, y, WALL_C));
}

bool		map_has_collision_objection_at(float x, float y)
{
	return (map_has_wall_at(x, y) || map_has_object_at(x, y));
}
