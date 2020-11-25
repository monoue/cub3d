/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 13:56:12 by monoue            #+#    #+#             */
/*   Updated: 2020/11/24 15:43:18 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_has_wall_at.h"

bool	map_has_wall_at(float x, float y)
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
	return (g_map[grid_y][grid_x] == WALL_C);
}
