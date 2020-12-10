/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_g_player_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 10:10:33 by monoue            #+#    #+#             */
/*   Updated: 2020/12/10 07:19:11 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_G_PLAYER_BONUS_H
# define INIT_G_PLAYER_BONUS_H

# include "../defs_bonus.h"

typedef struct	s_player {
	int		grid_x;
	int		grid_y;
	float	x;
	float	y;
	float	width;
	float	height;
	int		turn_direction;
	int		walk_direction;
	int		walk_horz;
	float	rotation_angle;
	float	walk_speed;
	float	turn_speed;
}				t_player;

extern			t_player g_player;

#endif
