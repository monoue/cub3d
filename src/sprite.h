/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:12:04 by monoue            #+#    #+#             */
/*   Updated: 2020/11/24 16:43:05 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_H
# define SPRITE_H

# include <unistd.h>

# include "defs.h"
# include "graphics.h"
# include "render_mini_map.h"

typedef struct	s_sprite {
	float	x;
	float	y;
	float	distance_from_player;
}				t_sprite;

extern t_sprite g_sprites[MAX_SPRITES_NUM];

void			set_sprite_basic_data(size_t x, size_t y, size_t sprite_i);
void			update_sprites_data(void);

#endif
