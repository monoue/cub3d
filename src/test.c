#include "test.h"
#include "defs.h"

static float	calc_angle_difference_between_player_and_sprite(size_t index)
{
	float		angle_from_player_to_sprite;
	const float	x_difference = g_sprites[index].x - g_player.x;
	const float	y_difference = g_sprites[index].y - g_player.y;
	float	angle_difference;
	
	angle_from_player_to_sprite = atan2f(y_difference, x_difference);
	angle_difference = g_player.rotation_angle - angle_from_player_to_sprite;
    if (angle_difference < -(PI))
        angle_difference += TWO_PI;
    if (angle_difference > PI)
        angle_difference -= TWO_PI;
	// return (fabsf(angle_difference));
	return (angle_difference);
}

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

void	test_sprite_hit(void)
{
	size_t	index;

	index = 0;
	while (index < g_cubfile_data.sprites_num)
	{
		DI(g_sprites[index].is_visible);
		index++;
	}
}

static void	test_sprite_center_vertical_line(size_t index)
{
	const float	angle_difference_between_player_and_sprite = calc_angle_difference_between_player_and_sprite(index);
	float	x_difference_between_window_center_and_sprite = (g_cubfile_data.window_width / FOV_ANGLE) * angle_difference_between_player_and_sprite;
	int		sprite_center_x = g_cubfile_data.window_width / 2 - (x_difference_between_window_center_and_sprite);
	g_color = create_trgb(0, 0, 255, 0);
	if (sprite_center_x >= 0 && sprite_center_x < g_cubfile_data.window_width)
	{
		for (int y = 0; y < g_cubfile_data.window_height; y++)
			draw_pixel(sprite_center_x, y);
	}
}

void	test_draw_sprite_center_vertical_lines(void)
{
	size_t	index;

	index = 0;
	while (index < g_cubfile_data.sprites_num)
	{
		test_sprite_center_vertical_line(index);
		index++;
	}
}