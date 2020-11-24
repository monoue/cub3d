#ifndef TEST_H
# define TEST_H
#include "create_maps.h"
#include "debug.h"
#include "defs.h"
#include "error.h"
// #include "init_mlx.h"
#include "map_error.h"
#include "player.h"
#include "set_color.h"
#include "set_cubfile_data.h"


void	test_all_cubfile_data(void);
void	test_current_g_map_to_check(void);
void	test_player_data(void);
void	test_texture_data(void);
void	test_ray_data(size_t index);
void	test_sprite_hit(void);
void	test_draw_sprite_center_vertical_lines(void);

#endif