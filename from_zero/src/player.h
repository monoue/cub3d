#ifndef PLAYER_H
# define PLAYER_H

# include "defs.h"
// # include "graphics.h"
// # include "map.h"

typedef struct	s_player {
	float	x;
	float	y;
	float	width;
	float	height;
	int		turn_direction;
	int		walk_direction;
	float	rotation_angle;
	float	walk_speed;
	float	turn_speed;
}				t_player;

extern t_player g_player;
void	set_player_spawning_data(size_t x, size_t y, char current_c);

// void	move_player(float deltaTime);
// void	render_player();

#endif