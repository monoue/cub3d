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
bool	mapHasWallAt(const float pixelX, const float pixelY);
bool	isInsideMap(float x, float y);
void	renderMap(void);
int		getMapAt(int y, int x);

bool	isOutOfWindow(const float x, const float y);
bool	isSpaceAt(const float pixelX, const float pixelY);

#endif