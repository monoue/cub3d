/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_g_sprites.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 11:37:34 by monoue            #+#    #+#             */
/*   Updated: 2020/11/25 11:38:34 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_G_SPRITES_H
# define INIT_G_SPRITES_H

# include "../defs.h"

typedef struct	s_sprite {
	float	x;
	float	y;
	float	distance_from_player;
}				t_sprite;

extern t_sprite g_sprites[MAX_SPRITES_NUM];

#endif
