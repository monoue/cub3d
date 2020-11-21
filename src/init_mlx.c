/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 10:13:55 by monoue            #+#    #+#             */
/*   Updated: 2020/11/20 23:21:26 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_mlx.h"

#include "test.h"

t_mlx	g_mlx;
t_img	g_img;


void	update(void)
{
	move_player();
	cast_all_rays_to_wall();
	sprites();
}

bool is_out_of_window(float x, float y)
{
	return (x < 0 || x >= MAX_MAP_LEN * TILE_SIZE || y < 0 || y >= MAX_MAP_LEN * TILE_SIZE);
}

int	main_loop(void *null)
{
	(void)null;
	update();
	g_color = create_trgb(0, 0, 0, 0);
	draw_rectangle(0, 0, g_cubfile_data.window_width, g_cubfile_data.window_height);
	render_background();
	render_sprites();
	render_mini_map();

	// if (flag)
	// save_image();

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
	mlx_hook(g_mlx.win_ptr, KEY_PRESS, KEY_PRESS_MASK, key_down, NULL);
	mlx_hook(g_mlx.win_ptr, KEY_RELEASE, KEY_RELEASE_MASK, key_up, NULL);
	// TODO: 17 から 33 に変える
	// mlx_hook(g_mlx.win_ptr, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK, finish_program, NULL);
	mlx_hook(g_mlx.win_ptr, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK, finish_program, NULL);
	// exit フラグを立てる
	//
	mlx_loop_hook(g_mlx.mlx_ptr, &main_loop, NULL);
	mlx_loop(g_mlx.mlx_ptr);
}