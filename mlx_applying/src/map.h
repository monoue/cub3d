#ifndef MAP_H
# define MAP_H

# include <stdbool.h>
# include "defs.h"
# include "graphics.h"

# define MAP_NUM_ROWS 13
# define MAP_NUM_COLS 20

// # define EDGE_COLOR 0xFFFFFFFF
// # define INNER_COLOR 0x00000000
// static const int map[MAP_NUM_ROWS][MAP_NUM_COLS];
bool	map_has_wall_at(const float pixel_x, const float pixel_y);
bool	is_inside_map(float x, float y);
void	render_map(void);
int		get_map_at(int y, int x);

bool	is_out_of_window(const float x, const float y);
bool	is_space_at(const float pixel_x, const float pixel_y);

#endif