// #include "main.h"
#include "player.h"

// これの代わりに、init_player みたいなのを作って、構造体に格納されたデータを使うようにする
t_player	g_player =
{
	.x = NOT_SET,
	.y = NOT_SET,
	.width = 1,
	.height = 1,
	.turn_direction = 0,
	.walk_direction = 0,
	.rotation_angle = PI / 2,
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
	g_player.x = (float)x;
	g_player.y = (float)y;
	g_player.rotation_angle = get_spawning_angle(current_c);
}