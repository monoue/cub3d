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
	bool	is_visible;
	// size_t	distance_order_from_player;
}				t_sprite;

extern t_sprite g_sprites[MAX_SPRITES_NUM];

void	set_sprite_basic_data(size_t x, size_t y, size_t sprite_i);
void	sprites(void);

#endif
