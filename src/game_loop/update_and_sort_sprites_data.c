/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_and_sort_sprites_data.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 12:04:28 by monoue            #+#    #+#             */
/*   Updated: 2020/11/27 10:05:16 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "update_and_sort_sprites_data.h"

static void	update_sprite_data(size_t index)
{
	set_distance_from_player(index);
	set_angle_diff_from_player(index);
	set_perp_distance_from_player(index);
	set_projected_tile_size(index);
	set_projection_edges(index);
}

static void	update_all_sprites_data(void)
{
	size_t	index;

	index = 0;
	while (index < g_cubfile_data.sprites_num)
	{
		update_sprite_data(index);
		index++;
	}
}

static void	sort_sprites(void)
{
	size_t		index;
	size_t		inner_i;
	t_sprite	tmp;

	if (g_cubfile_data.sprites_num < 2)
		return ;
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

void		update_and_sort_sprites_data(void)
{
	update_all_sprites_data();
	sort_sprites();
}
