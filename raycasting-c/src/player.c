/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 10:23:21 by monoue            #+#    #+#             */
/*   Updated: 2020/10/13 10:33:19 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

t_player	g_player =
{
	.x = WINDOW_WIDTH / 2,
	.y = WINDOW_HEIGHT / 2,
	.width = 1,
	.height = 1,
	.turn_direction = 0,
	.walk_direction = 0,
	.rotation_angle = PI / 2,
	.walk_speed = 100,
	.turn_speed = 45 * (PI / 180)
};

void	move_player(float delta_time)
{
	float		new_player_x;
	float		new_player_y;
	const float	move_step = g_player.walk_direction * g_player.walk_speed * delta_time;
	const float	move_x = cos(g_player.rotation_angle) * move_step;
	const float	move_y = sin(g_player.rotation_angle) * move_step;

	new_player_x = g_player.x;
	new_player_y = g_player.y;
	g_player.rotation_angle += g_player.turn_direction * g_player.turn_speed * delta_time;
	if (isSpaceAt(g_player.x + move_x, g_player.y))
		new_player_x += move_x;
	if (isSpaceAt(g_player.x, g_player.y + move_y))
		new_player_y += move_y;
	g_player.x = new_player_x;
	g_player.y = new_player_y;
}

void	render_player(void)
{
	draw_rect(
		g_player.x * MINIMAP_SCALE_FACTOR,
		g_player.y * MINIMAP_SCALE_FACTOR,
		g_player.width * MINIMAP_SCALE_FACTOR,
		g_player.height * MINIMAP_SCALE_FACTOR,
		0xFFFFFFFF);
}
