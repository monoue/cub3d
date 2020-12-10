/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_g_sprites_bonus.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 11:37:34 by monoue            #+#    #+#             */
/*   Updated: 2020/12/10 07:19:11 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_G_SPRITES_BONUS_H
# define INIT_G_SPRITES_BONUS_H

# include "../defs_bonus.h"

typedef struct	s_sprite {
	float	x;
	float	y;
	float	distance_from_player;
	float	perp_distance_from_player;
	float	angle_diff_from_player;
	int		projected_tile_size;
	int		projection_top;
	int		projection_bottom;
	int		projection_left_edge;
	int		projection_right_edge;
}				t_sprite;

extern t_sprite g_sprites[MAX_SPRITES_NUM];

#endif
