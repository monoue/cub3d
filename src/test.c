#include "test.h"
#include "defs.h"

void	test_all_cubfile_data(void)
{
	DI(g_cubfile_data.window_width);
	DI(g_cubfile_data.window_height);
	DI((int)g_cubfile_data.floor_color);
	DI((int)g_cubfile_data.ceiling_color);
	for (size_t t_i = 0; t_i < TEXTURES_NUM; t_i++)
		DS(g_textures[t_i].path);
}

void	test_current_g_map_to_check(void)
{
	for (int i = 0; i < MAX_MAP_LEN; i++)
		printf("%s\n", g_map_to_check[i]);
}

void	test_player_data(void)
{
	DI(g_player.grid_x);
	DI(g_player.grid_y);
	DF(g_player.x);
	DF(g_player.y);
	DF(g_player.width);
	DF(g_player.height);
	DI(g_player.turn_direction);
	DI(g_player.walk_direction);
	DF(g_player.rotation_angle);
	DF(g_player.walk_speed);
	DF(g_player.turn_speed);
}

void	test_texture_data(void)
{
	size_t	t_i;

	t_i = 0;
	while (t_i < TEXTURES_NUM)
	{
		DS(g_textures[t_i].addr);
		DI(g_textures[t_i].bits_per_pixel);
		DI(g_textures[t_i].line_length);
		DI(g_textures[t_i].endian);
		DI(g_textures[t_i].width);
		DI(g_textures[t_i].height);
		DS(g_textures[t_i].path);
		t_i++;
	}
}

void	test_ray_data(size_t index)
{
	DF(g_rays[index].ray_angle);
	DF(g_rays[index].wall_hit_coord->x);
	DF(g_rays[index].wall_hit_coord->y);
	DF(g_rays[index].distance);
	DI(g_rays[index].was_hit_vertical);
	// DC(g_rays[index].wall_hit_content);
}