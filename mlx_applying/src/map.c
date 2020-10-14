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

bool	is_out_of_window(const float x, const float y)
{
	return (x < 0 || x >= MAP_NUM_COLS * TILE_SIZE || y < 0 || y >= MAP_NUM_ROWS * TILE_SIZE);
}

bool	map_has_wall_at(const float pixel_x, const float pixel_y)
{
	if (is_out_of_window(pixel_x, pixel_y))
		return (true);
	const int grid_x = floor(pixel_x / TILE_SIZE);
	const int grid_y = floor(pixel_y / TILE_SIZE);
	return map[grid_y][grid_x] != 0 ? true : false;
}

bool is_inside_map(float x, float y) {
    return (x >= 0 && x <= MAP_NUM_COLS * TILE_SIZE && y >= 0 && y <= MAP_NUM_ROWS * TILE_SIZE);
}


int	get_map_at(int y, int x)
{
	return (map[y][x]);
}

void	render_map(void)
{
	int	y;
	int	x;

	y = 0;
	while (y < MAP_NUM_ROWS)
	{
		x = 0;
		while (x < MAP_NUM_COLS)
		{
			const int tile_x = x * TILE_SIZE;
			const int tile_y = y * TILE_SIZE;
			uint32_t tile_color = map[y][x] == 0 ? 0x00000000 : 0xFFFFFFFF;

			draw_rect(
				tile_x * MINIMAP_SCALE_FACTOR,
				tile_y * MINIMAP_SCALE_FACTOR,
				TILE_SIZE * MINIMAP_SCALE_FACTOR,
				TILE_SIZE * MINIMAP_SCALE_FACTOR,
				tile_color
			);
			x++;
		}
		y++;
	}
}

bool	is_space_at(const float pixel_x, const float pixel_y)
{
	if (is_out_of_window(pixel_x, pixel_y))
		return (false);
	const int grid_x = floor(pixel_x / TILE_SIZE);
	const int grid_y = floor(pixel_y / TILE_SIZE);
	return map[grid_y][grid_x] == 0 ? true : false;
}