#include "main.h"
#include "player.h"

// これの代わりに、init_player みたいなのを作って、構造体に格納されたデータを使うようにする
t_player	g_player =
{
	.x = NOT_SET,
	// .y = NOT_SET,
	.width = 1,
	.height = 1,
	.turn_direction = 0,
	.walk_direction = 0,
	// .rotation_angle = PI / 2,
	.walk_speed = 100,
	.turn_speed = 45 * (PI / 180)
};