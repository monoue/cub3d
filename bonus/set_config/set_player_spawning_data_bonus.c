/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player_spawning_data_bonus.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 16:25:25 by monoue            #+#    #+#             */
/*   Updated: 2020/12/09 16:45:27 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "set_player_spawning_data_bonus.h"

static float	get_spawning_angle(char c)
{
	if (c == 'E')
		return (0);
	if (c == 'S')
		return (PI * 0.5);
	if (c == 'W')
		return (PI);
	if (c == 'N')
		return (PI * 1.5);
	return (0);
}

void			set_player_spawning_data(size_t x, size_t y, char current_c)
{
	g_player.grid_x = x;
	g_player.grid_y = y;
	g_player.x = x * TILE_SIZE + TILE_SIZE * 0.5;
	g_player.y = y * TILE_SIZE + TILE_SIZE * 0.5;
	g_player.rotation_angle = get_spawning_angle(current_c);
}
