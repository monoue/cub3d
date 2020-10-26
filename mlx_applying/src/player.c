#include "player.h"

// これの代わりに、init_player みたいなのを作って、構造体に格納されたデータを使うようにする
t_player	g_player =
{
	.x = WINDOW_WIDTH / 2,
	.y = WINDOW_HEIGHT / 2,
	.width = 1,
	.height = 1,
	.turn_direction = 0,
	.walk_direction = 0,
	.rotation_angle = PI / 2,
	.walk_speed = 100,
	.turn_speed = 45 * (PI / 180)
};

void	move_player(float delta_time)
{
	g_player.rotation_angle += g_player.turn_direction * g_player.turn_speed * delta_time;

	const float	move_step = g_player.walk_direction * g_player.walk_speed * delta_time;
	const float	move_x = cos(g_player.rotation_angle) * move_step;
	const float	move_y = sin(g_player.rotation_angle) * move_step;

	float	new_player_x = g_player.x;
	float	new_player_y = g_player.y;

	if (is_space_at(g_player.x + move_x, g_player.y))
		new_player_x += move_x;
	if (is_space_at(g_player.x, g_player.y + move_y))
		new_player_y += move_y;

	g_player.x = new_player_x;
	g_player.y = new_player_y;

}

void	render_player()
{
	draw_rect(
		g_player.x * MINIMAP_SCALE_FACTOR,
		g_player.y * MINIMAP_SCALE_FACTOR,
		g_player.width * MINIMAP_SCALE_FACTOR,
		g_player.height * MINIMAP_SCALE_FACTOR,
		0xFFFFFFFF
	);
}
