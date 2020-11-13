/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 12:04:28 by monoue            #+#    #+#             */
/*   Updated: 2020/11/13 13:33:14 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprite.h"

t_sprite g_sprites[MAX_SPRITES_NUM];

void	set_sprite_data(size_t x, size_t y, size_t sprite_i)
{
	g_sprites[sprite_i].x = x * TILE_SIZE + TILE_SIZE * 0.5;
	g_sprites[sprite_i].y = y * TILE_SIZE + TILE_SIZE * 0.5;
}

void	set_distance_to_sprite(size_t index)
{
	float	delta_x;
	float	delta_y;

	delta_x = g_sprites[index].x - g_player.x;
	delta_y = g_sprites[index].y - g_player.y;
	g_sprites[index].distance_from_player = sqrt(pow(delta_x, 2) + pow(delta_x, 2));
}

void	update_distances_to_sprites(void)
{
	size_t	index;

	index = 0;
	while (index < g_cubfile_data.sprites_num)
	{
		set_distance_to_sprite(index);
		index++;
	}
}

void	sort_sprites(void)
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
			if (g_sprites[index].distance_from_player < g_sprites[inner_i].distance_from_player)
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

void	render_rays_to_sprites()
{
	size_t			index;
	const size_t	s_num = g_cubfile_data.sprites_num;

	index = 0;
	while (index < s_num)
	{
		g_color = create_trgb(0, floor(255 * index / (s_num - 1)), 50, floor(255 - 255 * (index / (s_num - 1))));
		draw_line(
			g_player.x * MINIMAP_SCALE_FACTOR,
			g_player.y * MINIMAP_SCALE_FACTOR,
			g_sprites[index].x * MINIMAP_SCALE_FACTOR,
			g_sprites[index].y * MINIMAP_SCALE_FACTOR);
		index++;
	}
}

void	sprites(void)
{
	update_distances_to_sprites();
	sort_sprites();
	render_rays_to_sprites();
}