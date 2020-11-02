/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 10:13:55 by monoue            #+#    #+#             */
/*   Updated: 2020/11/02 13:52:33 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx/mlx.h"
#include "init_mlx.h"

t_texture g_textures[TEXTURES_NUM];
t_mlx	g_mlx;
t_img	g_img;
# define ROWS 11
# define COLS 15
# define WIDTH COLS * TILE_SIZE
# define HEIGHT ROWS * TILE_SIZE
int		key_down(int keycode, void *null)
{
	(void)null;
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_W)
		g_player.walk_direction = FRONT;
	if (keycode == KEY_S)
		g_player.walk_direction = BACK;
	// if (keycode == KEY_A)
	// 	g_player.walk_direction = LEFT;
	// if (keycode == KEY_D)
	// 	g_player.walk_direction = RIGHT;
	if (keycode == KEY_LEFT)
		g_player.turn_direction = LEFT;
	if (keycode == KEY_RIGHT)
		g_player.turn_direction = RIGHT;
	return (0);
}

// int		key_up(int keycode, void *null)
// {
// 	(void)null;
// 	if (keycode == KEY_W)
// 		g_player.walk_direction = NEUTRAL;
// 	if (keycode == KEY_S)
// 		g_player.walk_direction = NEUTRAL;
// 	// if (keycode == KEY_A)
// 	// 	g_player.walk_direction = NEUTRAL;
// 	// if (keycode == KEY_D)
// 	// 	g_player.walk_direction = NEUTRAL;
// 	if (keycode == KEY_LEFT)
// 		g_player.turn_direction = NEUTRAL;
// 	if (keycode == KEY_RIGHT)
// 		g_player.turn_direction = NEUTRAL;
// 	return (0);
// }

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


// static void	set_textures()
// {
// 	size_t		t_i;
// 	t_texture	texture_i;

// 	t_i = 0;
// 	while (t_i < TEXTURES_NUM)
// 	{
// 		texture_i = g_textures[t_i];
// 		texture_i.img_ptr = mlx_xpm_file_to_image(g_mlx.mlx_ptr, texture_i.path, &texture_i.width, &texture_i.height);
// 		// TODO: エラーメッセージ、strerror で対処できるか後でやってみる
// 		if (texture_i.img_ptr == NULL)
// 			exit_with_error_message(SINGLE, "xpm file's data could not be read");
// 		texture_i.addr = mlx_get_data_addr(texture_i.img_ptr, &texture_i.bits_per_pixel, &texture_i.line_length, &texture_i.endian);
// 	}
// }

// void	zbuffer_init(t_data *img)
// {
// 	// zbuffer とは？？
// 	img->zbuffer = (double *)malloc(sizeof(double) * img->map.window_width);
// }

// int		render_next_frame(void *null)
// {
// 	(void)null;
// 	// int		x;

// 	// x = 0;
// 	// zbuffer_init(img);
// 	// ray_cast(img, x);
// 	// sprite_init(img);
// 	// sort_sprite(img);
// 	// x = 0;
// 	// sprites(img, x);
// 	// moves(img);
// 	// mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
// 	// free(img->zbuffer);
// 	return (0);
// }

// int	playerX, playerY;

// int	setup()
// {
// 	playerX = 0;
// 	playerY = 0;
// 	return (0);
// }

// int update()
// {
// 	playerX++;
// 	playerY++;
// 	return (0);
// }
void            my_mlx_pixel_put(int x, int y, t_color color)
{
    char    *dst;

    dst = g_img.data + (y * g_img.line_length + x * (g_img.bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void	draw_rectangle(int x, int y)
{
	int i;
	int j;

	// x *= TILE_SIZE;
	// y *= TILE_SIZE;
	i = 0;
	while (i < 5)
	{
		j = 0;
		while (j < 5)
		{
			my_mlx_pixel_put(x + j, y + i, 0x00FF0000);
			j++;
		}
		i++;
	}
}
// void	draw_rectangle(size_t start_x, size_t start_y, size_t width, size_t height, t_color color)
// {
// 	size_t	y_i;
// 	size_t	x_i;

// 	y_i = 0;
// 	while (y_i < height)
// 	{
// 		x_i = 0;
// 		while (x_i < width)
// 		{
// 			g_img.data[(start_y + y_i) * g_cubfile_data.window_width + start_x + x_i] = color;
// 			x_i++;
// 		}
// 		y_i++;
// 	}
// }

// int	render()
// {
// 	return (0);
// }

int	main_loop(void *null)
{
	(void)null;

	// t_color	color;

	// color = create_trgb(0, 255, 255, 255);
	// draw_rectangle(30, 30, 3, 3, color);
	draw_rectangle(5, 5);
	mlx_put_image_to_window(g_mlx.mlx_ptr, g_mlx.win_ptr, g_img.img_ptr, 0, 0);
	return (0);
}

void	mlx(void)
{
	g_mlx.mlx_ptr = mlx_init();
	g_mlx.win_ptr = mlx_new_window(g_mlx.mlx_ptr, WIDTH, HEIGHT, "Monoue's cub3D");
	g_img.img_ptr = mlx_new_image(g_mlx.mlx_ptr, WIDTH, HEIGHT);
	// g_img.data = (t_color *)mlx_get_data_addr(g_img.img_ptr, &g_img.bits_per_pixel, &g_img.line_length, &g_img.endian);
	g_img.data = mlx_get_data_addr(g_img.img_ptr, &g_img.bits_per_pixel, &g_img.line_length, &g_img.endian);
	// g_img.data = (int *)mlx_get_data_addr(g_img.img_ptr, &g_img.bits_per_pixel, &g_img.line_length, &g_img.endian);
	// g_mlx.mlx_ptr = mlx_init();
	// g_mlx.win_ptr = mlx_new_window(g_mlx.mlx_ptr, g_cubfile_data.window_width, g_cubfile_data.window_height, "Monoue's cub3D");
	// g_img.img_ptr = mlx_new_image(g_mlx.mlx_ptr, g_cubfile_data.window_width, g_cubfile_data.window_height);
	// g_img.data = (int *)mlx_get_data_addr(g_img.img_ptr, &g_img.bits_per_pixel, &g_img.line_length, &g_img.endian);

	// set_textures();
	// int		count_w;
	// int		count_h;

	// count_h = -1;
	// while (++count_h < g_cubfile_data.window_height)
	// {
	// 	count_w = -1;
	// 	while (++count_w < g_cubfile_data.window_width)
	// 	{
	// 		if (count_w % 2)
	// 			g_img.data[count_h * g_cubfile_data.window_width + count_w] = 0xFFFFFF;
	// 		else
	// 			g_img.data[count_h * g_cubfile_data.window_width + count_w] = 0xFF0000;
	// 	}
	// }



	// mlx_hook(g_mlx.win_ptr, KEY_PRESS, KEY_PRESS_MASK, key_down, NULL);
	// mlx_hook(g_mlx.win_ptr, KEY_RELEASE, KEY_RELEASE_MASK, key_up, NULL);
	// setup();
	// update();
	// render();
	mlx_hook(g_mlx.win_ptr, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK, finish_program, NULL);
	// mlx_loop_hook(g_mlx.mlx_ptr, render_next_frame, NULL);
	// mlx_put_image_to_window(g_mlx.mlx_ptr, g_mlx.win_ptr, g_img.img_ptr, 0, 0);
	// mlx_put_image_to_window(g_mlx.mlx_ptr, g_mlx.win_ptr, g_img.img_ptr, 0, 0);
	mlx_loop_hook(g_mlx.mlx_ptr, &main_loop, NULL);
	mlx_loop(g_mlx.mlx_ptr);
}