/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 10:13:55 by monoue            #+#    #+#             */
/*   Updated: 2020/11/16 10:25:13 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_mlx.h"

#include "test.h"

t_mlx	g_mlx;
t_img	g_img;


void	reset_sprites_texture_data(void)
{
	size_t	index;

	index = 0;
	while (index < g_cubfile_data.sprites_num)
	{
		g_sprites[index].is_visible = false;
		index++;
	}
}

bool	is_sprite_within_fov(size_t index)
{
	t_coord *vector;
	float	angle_from_player_to_sprite;
	float	angle_difference;

	vector = malloc(sizeof(vector));
	
	coord_assign(vector, g_sprites[index].x - g_player.x, g_sprites[index].y - g_player.y);
	angle_from_player_to_sprite = atan2f(vector->y, vector->x);
	angle_difference = g_player.rotation_angle - angle_from_player_to_sprite;
	normalize_angle(&angle_difference);
    if (angle_difference < -(PI))
        angle_difference += TWO_PI;
    if (angle_difference > PI)
        angle_difference -= TWO_PI;
	angle_difference = fabsf(angle_difference);
	return (angle_difference < FOV_ANGLE / 2);
}

void	record_sprites_within_fov(void)
{
	size_t	index;

	index = 0;
	while (index < g_cubfile_data.sprites_num)
	{
		if (is_sprite_within_fov(index))
			g_sprites[index].is_visible = true;
		index++;
	}
}

void	update(void)
{
	move_player();
	reset_sprites_texture_data();
	record_sprites_within_fov();
	cast_all_rays_to_wall();
	test_sprite_hit();
	// cast_all_rays();
}

bool is_out_of_window(float x, float y) {
	return (x < 0 || x >= MAX_MAP_LEN * TILE_SIZE || y < 0 || y >= MAX_MAP_LEN * TILE_SIZE);
}


int	main_loop(void *null)
{
	(void)null;
	update();
	g_color = create_trgb(0, 0, 0, 0);
	draw_rectangle(0, 0, g_cubfile_data.window_width, g_cubfile_data.window_height);
	render_background();
	render_mini_map();
	render_rays();
	sprites();
	render_player();
	mlx_put_image_to_window(g_mlx.mlx_ptr, g_mlx.win_ptr, g_img.img_ptr, 0, 0);
	mlx_do_sync(g_mlx.mlx_ptr);
	return (0);
}

void	mlx(void)
{
	g_mlx.mlx_ptr = mlx_init();
	g_mlx.win_ptr = mlx_new_window(g_mlx.mlx_ptr, g_cubfile_data.window_width, g_cubfile_data.window_height, "Monoue's cub3D");
	g_img.img_ptr = mlx_new_image(g_mlx.mlx_ptr, g_cubfile_data.window_width, g_cubfile_data.window_height);
	g_img.addr = mlx_get_data_addr(g_img.img_ptr, &g_img.bits_per_pixel, &g_img.line_length, &g_img.endian);

	set_textures();
	// test_texture_data();
	// test_player_data();
	mlx_hook(g_mlx.win_ptr, KEY_PRESS, KEY_PRESS_MASK, key_down, NULL);
	mlx_hook(g_mlx.win_ptr, KEY_RELEASE, KEY_RELEASE_MASK, key_up, NULL);
	// wall_texture の作成
	// setup();
	mlx_hook(g_mlx.win_ptr, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK, finish_program, NULL);
	mlx_loop_hook(g_mlx.mlx_ptr, &main_loop, NULL);
	mlx_loop(g_mlx.mlx_ptr);
}