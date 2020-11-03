#include "test.h"
#include "defs.h"

void	test_all_cubfile_data(void)
{
	DEBUGVD(g_cubfile_data.window_width);
	DEBUGVD(g_cubfile_data.window_height);
	DEBUGVD((int)g_cubfile_data.floor_color);
	DEBUGVD((int)g_cubfile_data.ceiling_color);
	for (size_t t_i = 0; t_i < TEXTURES_NUM; t_i++)
		DEBUGVS(g_textures[t_i].path);
}

void	test_current_g_map_to_check(void)
{
	for (int i = 0; i < MAX_MAP_LEN; i++)
		printf("%s\n", g_map_to_check[i]);
}

void	test_player_data(void)
{
	DEBUGVD(g_player.grid_x);
	DEBUGVD(g_player.grid_y);
	DEBUGVF(g_player.x);
	DEBUGVF(g_player.y);
	DEBUGVF(g_player.width);
	DEBUGVF(g_player.height);
	DEBUGVD(g_player.turn_direction);
	DEBUGVD(g_player.walk_direction);
	DEBUGVF(g_player.rotation_angle);
	DEBUGVF(g_player.walk_speed);
	DEBUGVF(g_player.turn_speed);
}
