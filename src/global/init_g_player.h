/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_g_player.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 10:10:33 by monoue            #+#    #+#             */
/*   Updated: 2020/11/25 10:10:55 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_G_PLAYER_H
# define INIT_G_PLAYER_H

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
