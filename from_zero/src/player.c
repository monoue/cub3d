// #include "main.h"
#include "player.h"

t_player	g_player =
{
	.x = NOT_SET,
	.y = NOT_SET,
	.width = 5,
	.height = 5,
	.turn_direction = NEUTRAL,
	.walk_direction = NEUTRAL,
	.walk_speed = 10,
	// .walk_speed = 2,
	// .turn_speed = 45 * (PI / 180)
	.turn_speed = 5 * (PI / 180)
	// .turn_speed = 1.0 * (PI / 180)
};

void	render_player(void)
{
	g_color = create_trgb(0, 0, 255, 255);
	draw_rectangle(
		g_player.x * MINIMAP_SCALE_FACTOR,
		g_player.y * MINIMAP_SCALE_FACTOR,
		g_player.width * MINIMAP_SCALE_FACTOR, g_player.height * MINIMAP_SCALE_FACTOR
	);
	draw_line(
		g_player.x * MINIMAP_SCALE_FACTOR,
		g_player.y * MINIMAP_SCALE_FACTOR,
		(g_player.x + cos(g_player.rotation_angle) * 40) * MINIMAP_SCALE_FACTOR,
		(g_player.y + sin(g_player.rotation_angle) * 40) * MINIMAP_SCALE_FACTOR
	);
}

void	move_player(void)
{
	float	moving_direction;
	moving_direction = g_player.rotation_angle + HALF_PI * g_player.walk_direction;
	normalize_angle(&moving_direction);
	float		new_player_x;
	float		new_player_y;

	g_player.rotation_angle += g_player.turn_direction * g_player.turn_speed;
	normalize_angle(&g_player.rotation_angle);
	if (g_player.walk_direction != NEUTRAL)
	{
		new_player_x = g_player.x + cos(moving_direction) * g_player.walk_speed;
		new_player_y = g_player.y + sin(moving_direction) * g_player.walk_speed;
		if (!map_has_wall_at(new_player_x, g_player.y))
			g_player.x = new_player_x;
		if (!map_has_wall_at(g_player.x, new_player_y))
			g_player.y = new_player_y;
	}
}

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
	g_player.x = x * TILE_SIZE + TILE_SIZE * 0.5;
	g_player.y = y * TILE_SIZE + TILE_SIZE * 0.5;
	g_player.rotation_angle = get_spawning_angle(current_c);
}