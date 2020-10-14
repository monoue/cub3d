#include "player.h"

// これの代わりに、init_player みたいなのを作って、構造体に格納されたデータを使うようにする
t_player	player =
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
	player.rotation_angle += player.turn_direction * player.turn_speed * delta_time;

	const float	move_step = player.walk_direction * player.walk_speed * delta_time;
	const float	move_x = cos(player.rotation_angle) * move_step;
	const float	move_y = sin(player.rotation_angle) * move_step;

	float	new_player_x = player.x;
	float	new_player_y = player.y;

	if (is_space_at(player.x + move_x, player.y))
		new_player_x += move_x;
	if (is_space_at(player.x, player.y + move_y))
		new_player_y += move_y;

	player.x = new_player_x;
	player.y = new_player_y;

}

void	render_player()
{
	draw_rect(
		player.x * MINIMAP_SCALE_FACTOR,
		player.y * MINIMAP_SCALE_FACTOR,
		player.width * MINIMAP_SCALE_FACTOR,
		player.height * MINIMAP_SCALE_FACTOR,
		0xFFFFFFFF
	);
}
