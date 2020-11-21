/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:11:02 by monoue            #+#    #+#             */
/*   Updated: 2020/11/21 16:45:12 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "defs.h"
# include "map_check.h"
// # include "graphics.h"

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
void			set_player_spawning_data(size_t x, size_t y, char current_c);

void			move_player(void);
void			render_player(void);

#endif
