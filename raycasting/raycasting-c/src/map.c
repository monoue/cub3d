#include "map.h"

static const int map[MAP_NUM_ROWS][MAP_NUM_COLS] =
{
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 2, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 5},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 5},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 5},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 5, 5, 5, 5, 5, 5}
};

bool	isOutOfWindow(const float x, const float y)
{
	return (x < 0 || x >= MAP_NUM_COLS * TILE_SIZE || y < 0 || y >= MAP_NUM_ROWS * TILE_SIZE);
}


bool	isSpaceAt(const float pixelX, const float pixelY)
{
	if (isOutOfWindow(pixelX, pixelY))
		return (false);
	const int gridX = floor(pixelX / TILE_SIZE);
	const int gridY = floor(pixelY / TILE_SIZE);
	return map[gridY][gridX] == 0 ? true : false;
}

bool	mapHasWallAt(const float pixelX, const float pixelY)
{
	if (isOutOfWindow(pixelX, pixelY))
		return (true);
	const int gridX = floor(pixelX / TILE_SIZE);
	const int gridY = floor(pixelY / TILE_SIZE);
	return map[gridY][gridX] != 0 ? true : false;
}

int	getMapAt(int y, int x)
{
	return (map[y][x]);
}

void	renderMap()
{
	int	y;
	int	x;

	y = 0;
	while (y < MAP_NUM_ROWS)
	{
		x = 0;
		while (x < MAP_NUM_COLS)
		{
			const int tileX = x * TILE_SIZE;
			const int tileY = y * TILE_SIZE;
			const int tileColor = map[y][x] == 0 ? INNER_COLOR : EDGE_COLOR;

			drawRect(
				tileX * MINIMAP_SCALE_FACTOR,
				tileY * MINIMAP_SCALE_FACTOR,
				TILE_SIZE * MINIMAP_SCALE_FACTOR,
				TILE_SIZE * MINIMAP_SCALE_FACTOR,
				tileColor
			);
			x++;
		}
		y++;
	}
}