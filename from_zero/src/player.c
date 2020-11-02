// #include "main.h"
#include "player.h"

t_player	g_player =
{
	.x = NOT_SET,
	// .y = NOT_SET,
	.width = 1,
	.height = 1,
	.turn_direction = NEUTRAL,
	.walk_direction = NEUTRAL,
	// .rotation_angle = PI / 2,
	.walk_speed = 100,
	.turn_speed = 45 * (PI / 180)
};

static float	get_spawning_angle(char c)
{
	if (c == 'E')
		return (0);
	if (c == 'S')
		return (PI * 0.5);
	if (c == 'W')
		return (PI);
	if (c == 'N')
		return (PI * 1.5);
	return (0);
}

void	set_player_spawning_data(size_t x, size_t y, char current_c)
{
	g_player.grid_x = x;
	g_player.grid_y = y;
	// 下の二つは、どうにか消せるような気がする。
	// x を突っ込んだら x * TILE_SIZE + TILE_SIZE * 0.5 を返す
	// 関数を作って、最初の setup の時だけ使ってやればいい
	g_player.x = x * TILE_SIZE + TILE_SIZE * 0.5;
	g_player.y = y * TILE_SIZE + TILE_SIZE * 0.5;
	g_player.rotation_angle = get_spawning_angle(current_c);
}