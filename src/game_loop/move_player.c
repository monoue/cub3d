/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 16:25:25 by monoue            #+#    #+#             */
/*   Updated: 2020/11/25 11:13:56 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "move_player.h"

void			move_player(void)
{
	float	moving_direction;
	float	new_player_x;
	float	new_player_y;

	moving_direction =
				g_player.rotation_angle + HALF_PI * g_player.walk_direction;
	normalize_angle(&moving_direction);
	g_player.rotation_angle += g_player.turn_direction * g_player.turn_speed;
	normalize_angle(&g_player.rotation_angle);
	if (g_player.walk_direction != NEUTRAL)
	{
		new_player_x = g_player.x + cos(moving_direction) * g_player.walk_speed;
		new_player_y = g_player.y + sin(moving_direction) * g_player.walk_speed;
		if (!map_has_wall_at(new_player_x, g_player.y))
			g_player.x = new_player_x;
		if (!map_has_wall_at(g_player.x, new_player_y))
			g_player.y = new_player_y;
	}
}
