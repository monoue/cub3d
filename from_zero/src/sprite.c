/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 12:04:28 by monoue            #+#    #+#             */
/*   Updated: 2020/11/10 13:43:44 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sprite.h"

t_sprite g_sprites[MAX_SPRITES_NUM];

void	set_sprite_data(size_t x, size_t y, size_t sprite_i)
{
	g_sprites[sprite_i].x = x * TILE_SIZE + TILE_SIZE * 0.5;
	g_sprites[sprite_i].y = y * TILE_SIZE + TILE_SIZE * 0.5;
}