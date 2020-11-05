/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 10:13:55 by monoue            #+#    #+#             */
/*   Updated: 2020/11/05 15:20:47 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	init_texture_paths(void)
{
	size_t	t_i;

	t_i = 0;
	while (t_i < TEXTURES_NUM)
	{
		g_textures[t_i].path = NULL;
		t_i++;
	}
}

static void	set_textures(void)
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


void	render_map(void)
{
	size_t	y_i;
	size_t	x_i;
	size_t	tile_x;
	size_t	tile_y;

	y_i = 0;
	while (g_map[y_i][0] != '\0')
	{
		x_i = 0;
		while (g_map[y_i][x_i] != '\0')
		{
			tile_x = TILE_SIZE * x_i;
			tile_y = TILE_SIZE * y_i;
			if (g_map[y_i][x_i] == '1')
				g_color = create_trgb(0, 255, 255, 255);
			else
				g_color = create_trgb(0, 0, 0, 0);
			draw_rectangle(
				tile_x * MINIMAP_SCALE_FACTOR,
				tile_y * MINIMAP_SCALE_FACTOR,
				TILE_SIZE * MINIMAP_SCALE_FACTOR,
				TILE_SIZE * MINIMAP_SCALE_FACTOR
			);
			x_i++;
		}
		y_i++;
	}
}


bool	map_has_wall_at(float x, float y)
{
	int grid_x;
	int grid_y;

	grid_x = floor(x / TILE_SIZE);
	grid_y = floor(y / TILE_SIZE);
	if (grid_x < 0)
		grid_x = 0;
	if (grid_x > MAX_MAP_LEN)
		grid_x = MAX_MAP_LEN;
	if (grid_y < 0)
		grid_y = 0;
	if (grid_y > MAX_MAP_LEN)
		grid_y = MAX_MAP_LEN;
	return (g_map[grid_y][grid_x] == '1');
}

bool	is_space_at(const float pixel_x, const float pixel_y)
{
	int grid_x = floor(pixel_x / TILE_SIZE);
	int grid_y = floor(pixel_y / TILE_SIZE);

	if (is_out_of_window(pixel_x, pixel_y))
		return (false);
	if (grid_x < 0)
		grid_x = 0;
	if (grid_x > MAX_MAP_LEN)
		grid_x = MAX_MAP_LEN;
	if (grid_y < 0)
		grid_y = 0;
	if (grid_y > MAX_MAP_LEN)
		grid_y = MAX_MAP_LEN;
	return (g_map[grid_y][grid_x] == '1' ? false : true);
}

void	update(void)
{
	move_player();
	cast_all_rays();
}

/*
** Unlike our natural view, the view in the screen is rectangle shaped.
** Therefore, we need to cut the cub3D world's view to "projection plane".
** "distance_proj_plane" is how far the player is from the projection plane.
** The field of view's edges are the edges of the window width.
** 
** tanjent (FOV_ANGLE / 2) = (window_width / 2) / distance_proj_plane
** actual height(= TILE_SIZE) : projected height = actual distance : distance_proj_plane
*/
void	generate_3d_projection(void)
{
	int		r_i;
	float	distance_proj_plane;
	float	projected_wall_height;
	int		wall_strip_height;
	int		wall_top_pixel;
	int		wall_bottom_pixel;
	int		h_i;
	float	perp_distance;

	r_i = 0;
	// while (r_i < NUM_RAYS)
	while (r_i < g_cubfile_data.window_width)
	{
		perp_distance = rays[r_i].distance * cos(rays[r_i].ray_angle - g_player.rotation_angle);
		distance_proj_plane = (g_cubfile_data.window_width / 2) / tan(FOV_ANGLE / 2);
		// projected_wall_height = (TILE_SIZE / rays[r_i].distance) * distance_proj_plane;
		projected_wall_height = (TILE_SIZE / perp_distance) * distance_proj_plane;

		wall_strip_height = (int)projected_wall_height;
		wall_top_pixel = (g_cubfile_data.window_height / 2) - (wall_strip_height / 2);
		if (wall_top_pixel < 0)
			wall_top_pixel = 0;
		wall_bottom_pixel = (g_cubfile_data.window_height / 2) + (wall_strip_height / 2);
		if (wall_bottom_pixel > g_cubfile_data.window_height)
			wall_bottom_pixel = g_cubfile_data.window_height;
		h_i = wall_top_pixel;
		g_color = create_trgb(0, 0, 128, 255);
		while (h_i < wall_bottom_pixel)	
		{
			draw_pixel(r_i, h_i);
			h_i++;
		}
		r_i++;
	}
}

int	main_loop(void *null)
{
	(void)null;
	update();
	g_color = create_trgb(0, 0, 0, 0);
	draw_rectangle(0, 0, g_cubfile_data.window_width, g_cubfile_data.window_height);
	generate_3d_projection();
	render_map();
	render_rays();
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