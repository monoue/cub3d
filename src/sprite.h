#ifndef SPRITE_H
# define SPRITE_H

# include <unistd.h>

# include "defs.h"

typedef struct	s_sprite {
	float	x;
	float	y;	
	float	distance;
}				t_sprite;

extern t_sprite g_sprites[MAX_SPRITES_NUM];

void	set_sprite_data(size_t x, size_t y, size_t sprite_i);

#endif
