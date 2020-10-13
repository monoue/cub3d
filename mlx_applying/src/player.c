#include "player.h"

// これの代わりに、init_player みたいなのを作って、構造体に格納されたデータを使うようにする
t_player	player =
{
	.x = WINDOW_WIDTH / 2,
	.y = WINDOW_HEIGHT / 2,
	.width = 1,
	.height = 1,
	.turnDirection = 0,
	.walkDirection = 0,
	.rotationAngle = PI / 2,
	.walkSpeed = 100,
	.turnSpeed = 45 * (PI / 180)
};

void	move_player(float deltaTime)
{
	player.rotation_angle += player.turn_direction * player.turn_speed * deltaTime;

	const float	moveStep = player.walk_direction * player.walk_speed * deltaTime;
	const float	moveX = cos(player.rotation_angle) * moveStep;
	const float	moveY = sin(player.rotation_angle) * moveStep;

	float	newPlayerX = player.x;
	float	newPlayerY = player.y;

	if (isSpaceAt(player.x + moveX, player.y))
		newPlayerX += moveX;
	if (isSpaceAt(player.x, player.y + moveY))
		newPlayerY += moveY;

	player.x = newPlayerX;
	player.y = newPlayerY;

}

void	renderPlayer()
{
	draw_rect(
		player.x * MINIMAP_SCALE_FACTOR,
		player.y * MINIMAP_SCALE_FACTOR,
		player.width * MINIMAP_SCALE_FACTOR,
		player.height * MINIMAP_SCALE_FACTOR,
		0xFFFFFFFF
	);
}
