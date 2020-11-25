/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sprites_data.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 12:04:28 by monoue            #+#    #+#             */
/*   Updated: 2020/11/25 07:32:25 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "update_sprites_data.h"

static void	set_distance_to_sprite(size_t index)
{
	const float delta_x = g_sprites[index].x - g_player.x;
	const float delta_y = g_sprites[index].y - g_player.y;

	g_sprites[index].distance_from_player = sqrt(pow(delta_x, 2)
															+ pow(delta_y, 2));
}

static void	update_distances_to_sprites(void)
{
	size_t	index;

	index = 0;
	while (index < g_cubfile_data.sprites_num)
	{
		set_distance_to_sprite(index);
		index++;
	}
}

static void	sort_sprites(void)
{
	size_t		index;
	size_t		inner_i;
	t_sprite	tmp;

	index = 0;
	while (index < g_cubfile_data.sprites_num - 1)
	{
		inner_i = index + 1;
		while (inner_i < g_cubfile_data.sprites_num)
		{
			if (g_sprites[index].distance_from_player
									< g_sprites[inner_i].distance_from_player)
			{
				tmp = g_sprites[index];
				g_sprites[index] = g_sprites[inner_i];
				g_sprites[inner_i] = tmp;
			}
			inner_i++;
		}
		index++;
	}
}

void		update_sprites_data(void)
{
	update_distances_to_sprites();
	sort_sprites();
}
