/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sprite_position.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:12:04 by monoue            #+#    #+#             */
/*   Updated: 2020/11/25 07:36:33 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_SPRITE_POSITON_H
# define SET_SPRITE_POSITION_H

# include "src/defs.h"

typedef struct	s_sprite {
	float	x;
	float	y;
	float	distance_from_player;
}				t_sprite;

extern t_sprite g_sprites[MAX_SPRITES_NUM];

void			set_sprite_position(size_t x, size_t y, size_t sprite_i);

#endif
