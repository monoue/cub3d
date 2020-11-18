#ifndef WALL_H
# define WALL_H

# include "defs.h"
# include "graphics.h" // g_color
# include "texture.h"

extern float	g_distance_proj_plane;

void	set_texture_color(t_texture texture, int x, int y);
void	render_background(void);

#endif
