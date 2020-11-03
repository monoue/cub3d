/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 10:13:55 by monoue            #+#    #+#             */
/*   Updated: 2020/11/03 10:15:39 by monoue           ###   ########.fr       */
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
		g_player.turn_direction = LEFT;
	if (keycode == KEY_RIGHT)
		g_player.turn_direction = RIGHT;
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
		texture_i = g_textures[t_i];
		texture_i.img_ptr = mlx_xpm_file_to_image(g_mlx.mlx_ptr, texture_i.path, &texture_i.width, &texture_i.height);
		// TODO: エラーメッセージ、strerror で対処できるか後でやってみる
		if (texture_i.img_ptr == NULL)
			exit_with_error_message(SINGLE, "xpm file's data could not be read");
		texture_i.addr = mlx_get_data_addr(texture_i.img_ptr, &texture_i.bits_per_pixel, &texture_i.line_length, &texture_i.endian);
		t_i++;
	}
}

void	draw_pixel(int x, int y, t_color color)
{
    char    *dst;

    dst = g_img.data + (y * g_img.line_length + x * (g_img.bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void	draw_rectangle(size_t start_x, size_t start_y, size_t width, size_t height, t_color color)
{
	size_t	y_i;
	size_t	x_i;

	y_i = 0;
	while (y_i < height)
	{
		x_i = 0;
		while (x_i < width)
		{
			draw_pixel(start_x + x_i, start_y + y_i, color);
			x_i++;
		}
		y_i++;
	}
}

void	draw_line(int x0, int y0, int x1, int y1, t_color color)
{
	int		delta_x;
	int		delta_y;
	size_t	longer_side_length;
	size_t	index;
	float	x_increment;
	float	y_increment;
	float	current_x;
	float	current_y;

	delta_x = (x1 - x0);
	delta_y = (y1 - y0);
	if (abs(delta_x) >= abs(delta_y))
		longer_side_length = abs(delta_x);
	else
		longer_side_length = abs(delta_y);
	x_increment = delta_x / (float)longer_side_length;
	y_increment = delta_y / (float)longer_side_length;
	current_x = x0;
	current_y = y0;
	index = 0;
	while (index < longer_side_length)
	{
		draw_pixel(round(current_x), round(current_y), color);
		current_x += x_increment;
		current_y += y_increment;
		index++;
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
				tile_color = 0x00FFFFFF;
			else
				tile_color = 0x00000000;
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

void	move_player(void)
{
	float	move_step;
	float	new_player_x;
	float	new_player_y;

	g_player.rotation_angle += g_player.turn_direction * g_player.turn_speed;
	move_step = g_player.walk_direction * g_player.walk_speed;
	new_player_x = g_player.x + cos(g_player.rotation_angle) * move_step;
	new_player_y = g_player.y + sin(g_player.rotation_angle) * move_step;
	g_player.x = new_player_x;
	g_player.y = new_player_y;
}

void	update(void)
{
	move_player();
}

int	main_loop(void *null)
{
	(void)null;
	update();
	draw_rectangle(0, 0, g_cubfile_data.window_width, g_cubfile_data.window_height, 0x00000000);
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