/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 10:13:55 by monoue            #+#    #+#             */
/*   Updated: 2020/11/03 14:11:10 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx/mlx.h"
#include "init_mlx.h"

#include "test.h"

t_texture g_textures[TEXTURES_NUM];
t_mlx	g_mlx;
t_img	g_img;
// # define ROWS 11
// # define COLS 15
// # define WIDTH COLS * TILE_SIZE
// # define HEIGHT ROWS * TILE_SIZE
int		key_down(int keycode, void *null)
{
	(void)null;
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_W)
		g_player.walk_direction = FRONT;
	if (keycode == KEY_S)
		g_player.walk_direction = BACK;
	if (keycode == KEY_A)
		g_player.walk_direction = LEFT;
	if (keycode == KEY_D)
		g_player.walk_direction = RIGHT;
	if (keycode == KEY_LEFT)
		g_player.turn_direction = TO_LEFT;
	if (keycode == KEY_RIGHT)
		g_player.turn_direction = TO_RIGHT;
	return (0);
}

int		key_up(int keycode, void *null)
{
	(void)null;
	if (keycode == KEY_W)
		g_player.walk_direction = NEUTRAL;
	if (keycode == KEY_S)
		g_player.walk_direction = NEUTRAL;
	if (keycode == KEY_A)
		g_player.walk_direction = NEUTRAL;
	if (keycode == KEY_D)
		g_player.walk_direction = NEUTRAL;
	if (keycode == KEY_LEFT)
		g_player.turn_direction = NEUTRAL;
	if (keycode == KEY_RIGHT)
		g_player.turn_direction = NEUTRAL;
	return (0);
}

int		finish_program(void *null)
{
	(void)null;
	// free 関係？
	mlx_destroy_window(g_mlx.mlx_ptr, g_mlx.mlx_ptr);
	mlx_destroy_image(g_mlx.mlx_ptr, g_img.img_ptr);
	exit(0);
	return (0);
}

// TODO: 悩んでいても進まない！　とにかく、一旦そのままなぞる！　最後にまとめてリファクタリング！


void	init_texture_paths()
{
	size_t	t_i;

	t_i = 0;
	while (t_i < TEXTURES_NUM)
	{
		g_textures[t_i].path = NULL;
		t_i++;
	}
}

static void	set_textures()
{
	size_t		t_i;
	t_texture	texture_i;

	t_i = 0;
	while (t_i < TEXTURES_NUM)
	{
		// これ、本当に動いているんだっけ？？
		texture_i = g_textures[t_i];
		texture_i.img_ptr = mlx_xpm_file_to_image(g_mlx.mlx_ptr, texture_i.path, &texture_i.width, &texture_i.height);
		// TODO: エラーメッセージ、strerror で対処できるか後でやってみる
		if (texture_i.img_ptr == NULL)
			exit_with_error_message(SINGLE, "xpm file's data could not be read");
		texture_i.addr = mlx_get_data_addr(texture_i.img_ptr, &texture_i.bits_per_pixel, &texture_i.line_length, &texture_i.endian);
		t_i++;
	}
}


void	render_map()
{
	size_t	y_i;
	size_t	x_i;
	size_t	tile_x;
	size_t	tile_y;
	t_color	tile_color;

	y_i = 0;
	while (g_map[y_i][0] != '\0')
	{
		x_i = 0;
		while (g_map[y_i][x_i] != '\0')
		{
			tile_x = TILE_SIZE * x_i;
			tile_y = TILE_SIZE * y_i;
			if (g_map[y_i][x_i] == '1')
				tile_color = create_trgb(0, 255, 255, 255);
			else
				tile_color = create_trgb(0, 0, 0, 0);
			draw_rectangle(
				tile_x * MINIMAP_SCALE_FACTOR,
				tile_y * MINIMAP_SCALE_FACTOR,
				TILE_SIZE * MINIMAP_SCALE_FACTOR,
				TILE_SIZE * MINIMAP_SCALE_FACTOR,
				tile_color
			);
			x_i++;
		}
		y_i++;
	}
}

void	render_player()
{
	draw_rectangle(
		g_player.x * MINIMAP_SCALE_FACTOR,
		g_player.y * MINIMAP_SCALE_FACTOR,
		g_player.width * MINIMAP_SCALE_FACTOR, g_player.height * MINIMAP_SCALE_FACTOR,
		create_trgb(0, 0, 255, 255)
	);
	draw_line(
		g_player.x * MINIMAP_SCALE_FACTOR,
		g_player.y * MINIMAP_SCALE_FACTOR,
		(g_player.x + cos(g_player.rotation_angle) * 40) * MINIMAP_SCALE_FACTOR,
		(g_player.y + sin(g_player.rotation_angle) * 40) * MINIMAP_SCALE_FACTOR,
		create_trgb(0, 0, 255, 255)
	);
}

bool	map_has_wall_at(float x, float y)
{
	size_t	grid_x;
	size_t	grid_y;

	grid_x = floor(x / TILE_SIZE);
	grid_y = floor(y / TILE_SIZE);
	return (g_map[grid_x][grid_y] == '1');
}

void	move_player(void)
{
	const float	moving_direction = g_player.rotation_angle + HALF_PI * g_player.walk_direction;
	float		new_player_x;
	float		new_player_y;

	g_player.rotation_angle += g_player.turn_direction * g_player.turn_speed;
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

void	update(void)
{
	move_player();
	// cast_all_rays();
}

int	main_loop(void *null)
{
	(void)null;
	update();
	draw_rectangle(0, 0, g_cubfile_data.window_width, g_cubfile_data.window_height, create_trgb(0, 0, 0, 0));
	render_map();
	// render_rays();
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
	g_img.data = mlx_get_data_addr(g_img.img_ptr, &g_img.bits_per_pixel, &g_img.line_length, &g_img.endian);

	set_textures();
	// test_player_data();
	mlx_hook(g_mlx.win_ptr, KEY_PRESS, KEY_PRESS_MASK, key_down, NULL);
	mlx_hook(g_mlx.win_ptr, KEY_RELEASE, KEY_RELEASE_MASK, key_up, NULL);
	// setup();
	mlx_hook(g_mlx.win_ptr, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK, finish_program, NULL);
	mlx_loop_hook(g_mlx.mlx_ptr, &main_loop, NULL);
	mlx_loop(g_mlx.mlx_ptr);
}