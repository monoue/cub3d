#ifndef PLAYER_H
# define PLAYER_H

# include "defs.h"
# include "graphics.h"
# include "map.h"

typedef struct	s_player {
	float	x;
	float	y;
	float	width;
	float	height;
	int		turnDirection;
	int		walkDirection;
	float	rotationAngle;
	float	walkSpeed;
	float	turnSpeed;
}				t_player;

extern t_player	player;

void	movePlayer(float deltaTime);
void	renderPlayer();
#endif