/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_hit_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 14:15:09 by monoue            #+#    #+#             */
/*   Updated: 2020/12/09 16:45:36 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "seek_hit_utils_bonus.h"

static float	distance_between_points(float x1, float y1, float x2, float y2)
{
	const float	x_diff = x2 - x1;
	const float	y_diff = y2 - y1;

	return (sqrt(pow(x_diff, 2) + pow(y_diff, 2)));
}

float			get_hit_distance(t_coord *wall_hit_coord, bool is_hit_found)
{
	float	hit_distance;

	if (is_hit_found == true)
	{
		hit_distance = distance_between_points(
			g_player.x,
			g_player.y,
			wall_hit_coord->x,
			wall_hit_coord->y);
	}
	else
		hit_distance = FLT_MAX;
	return (hit_distance);
}

bool			is_inside_map(t_coord *coord)
{
	const float		x = coord->x;
	const float		y = coord->y;
	const size_t	edge = MAX_MAP_LEN * TILE_SIZE;

	return (x >= 0 && x <= edge && y >= 0 && y <= edge);
}
