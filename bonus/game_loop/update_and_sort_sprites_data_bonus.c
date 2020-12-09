/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_and_sort_sprites_data_bonus.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 12:04:28 by monoue            #+#    #+#             */
/*   Updated: 2020/12/09 16:45:27 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "update_and_sort_sprites_data_bonus.h"

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
	while (index < g_config.sprites_num)
	{
		update_sprite_data(index);
		index++;
	}
}

void		update_and_sort_sprites_data(void)
{
	int	sprites_num;

	sprites_num = (int)g_config.sprites_num;
	update_all_sprites_data();
	sort_sprites();
}
