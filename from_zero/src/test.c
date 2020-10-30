#include "test.h"
#include "defs.h"

void	put_all_cubfile_data(void)
{
	DEBUGVD(g_cubfile_data.window_width);
	DEBUGVD(g_cubfile_data.window_height);
	DEBUGVD((int)g_cubfile_data.floor_color);
	DEBUGVD((int)g_cubfile_data.ceiling_color);
	for (size_t t_i = 0; t_i < TEXTURES_NUM; t_i++)
		DEBUGVS(g_textures[t_i].path);
}

void	put_current_g_map_to_check()
{
	for (int i = 0; i < MAX_MAP_LEN; i++)
		printf("%s\n", g_map_to_check[i]);
}