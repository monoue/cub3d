#ifndef SPRITE_H
# define SPRITE_H

# include <unistd.h>

# include "defs.h"
# include "graphics.h"

typedef struct	s_sprite {
	float	x;
	float	y;	
	float	distance_from_player;
	size_t	distance_from_left;
	bool	ray_hit;
	// size_t	distance_order_from_player;
}				t_sprite;

extern t_sprite g_sprites[MAX_SPRITES_NUM];

void	set_sprite_data(size_t x, size_t y, size_t sprite_i);
void	sprites(void);

#endif
