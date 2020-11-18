/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 10:13:55 by monoue            #+#    #+#             */
/*   Updated: 2020/11/18 15:03:55 by monoue           ###   ########.fr       */
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

// bool	is_sprite_within_fov(size_t index)
// {
// 	t_coord *vector;
// 	float	angle_from_player_to_sprite;
// 	float	angle_difference;

// 	vector = malloc(sizeof(vector));

// 	coord_assign(vector, g_sprites[index].x - g_player.x, g_sprites[index].y - g_player.y);
// 	angle_from_player_to_sprite = atan2f(vector->y, vector->x);
// 	angle_difference = g_player.rotation_angle - angle_from_player_to_sprite;
// 	// normalize_angle(&angle_difference);
//     if (angle_difference < -(PI))
//         angle_difference += TWO_PI;
//     if (angle_difference > PI)
//         angle_difference -= TWO_PI;
// 	angle_difference = fabsf(angle_difference);
// 	return (angle_difference < FOV_ANGLE / 2);
// }

// void	record_sprites_within_fov(void)
// {
// 	size_t	index;

// 	index = 0;
// 	while (index < g_cubfile_data.sprites_num)
// 	{
// 		if (is_sprite_within_fov(index))
// 			g_sprites[index].is_visible = true;
// 		index++;
// 	}
// }
float	calc_angle_difference_between_player_and_sprite(size_t index)
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


// 角度一度あたりの横幅を出し、それに角度分を掛けてやっている。
// void	draw_green_line_vertically(size_t index)
// {
// 	const float	angle_difference_between_player_and_sprite = calc_angle_difference_between_player_and_sprite(index);

// 	// const float	distance_proj_plane = (g_cubfile_data.window_width / 2) / tan(FOV_ANGLE / 2);
// 	float	x_difference_from_center = (g_cubfile_data.window_width / FOV_ANGLE) * angle_difference_between_player_and_sprite;
// 	// float	base_distance = fabs(g_sprites[index].distance_from_player * cos(angle_difference_between_player_and_sprite / PI * 180));
// 	// int		start_x = g_cubfile_data.window_width / 2 - (x_difference_from_center) - (TILE_SIZE / 2 * distance_proj_plane / base_distance);
// 	// int		start_x = g_cubfile_data.window_width / 2 - (x_difference_from_center) - (TILE_SIZE / 2 * base_distance / distance_proj_plane);
// 	// int		start_x = g_cubfile_data.window_width / 2 - (x_difference_from_center) - (TILE_SIZE / 2);
// 	// これは真ん中
// 	// int		start_x = g_cubfile_data.window_width / 2 - (x_difference_from_center);
// 	int		start_x = g_cubfile_data.window_width / 2 - (x_difference_from_center);
// 	int	sprite_screen_left_x = start_x - (strip_h / 2);
// 	g_color = create_trgb(0, 0, 255, 0);
// 	if (start_x >= 0 && start_x < g_cubfile_data.window_width)
// 	{
// 		int	y = 0;
// 		while (y < g_cubfile_data.window_height)
// 		{
// 			draw_pixel(start_x, y);
// 			y++;
// 		}
// 	}
// }

// int		calc_projected_strip_height(t_ray_to_wall ray)
// int		calc_projected_strip_height(void)
// {
// 	// const float	distance_proj_plane
// 	// 				= (g_cubfile_data.window_width / 2) / tan(FOV_ANGLE / 2);
// 	// const float perp_distance_to_wall
// 	// 	= ray.distance * cos(ray.ray_angle - g_player.rotation_angle);

// 	return ((int)(distance_proj_plane * (TILE_SIZE / perp_distance_to_wall)));
// }

// void	draw_sprite_center_vertical_line(size_t index)
// {
// 	const float	angle_difference_between_player_and_sprite = calc_angle_difference_between_player_and_sprite(index);

// 	// const float	distance_proj_plane = (g_cubfile_data.window_width / 2) / tan(FOV_ANGLE / 2);
// 	float	x_difference_from_center = (g_cubfile_data.window_width / FOV_ANGLE) * angle_difference_between_player_and_sprite;
// 	// こっちは絶対値(abs)版
// 	// float	base_distance = fabs(g_sprites[index].distance_from_player * cos(angle_difference_between_player_and_sprite / PI * 180));
// 	// float	base_distance = g_sprites[index].distance_from_player * cos(angle_difference_between_player_and_sprite / PI * 180);
// 	// float	strip_height = (int)(TILE_SIZE * (distance_proj_plane / base_distance));
// 	int		start_x = g_cubfile_data.window_width / 2 - (x_difference_from_center);
// 	// int		sprite_projection_left_x = start_x - (strip_height / 2);
// 	// int		sprite_projection_right_x = start_x + (strip_height / 2);
// 	// int sprite_projection_width = sprite_projection_right_x - sprite_projection_left_x;
// 	g_color = create_trgb(0, 0, 255, 0);
// 	if (start_x >= 0 && start_x < g_cubfile_data.window_width)
// 	{
// 		for (int y = 0; y < g_cubfile_data.window_height; y++)
// 			draw_pixel(start_x, y);
// 	}
// 	// while (sprite_projection_left_x < sprite_projection_right_x)
// 	// {
// 	// 	if (sprite_projection_left_x < 0 || sprite_projection_left_x >= g_cubfile_data.window_width)
// 	// 		;
// 	// 	else
// 	// 	{
// 	// 		int y = 0;
// 	// 		while (y < g_cubfile_data.window_height)
// 	// 		{
// 	// 			draw_pixel(sprite_projection_left_x, y);
// 	// 			y++;
// 	// 		}
// 	// 	}
// 	// 	sprite_projection_left_x++;
// 	// }

// }
void	render_from_top_to_sprite_ray_basis(int window_x, int *window_y, const int projected_sprite_height)
{
	const int sprite_top_pixel = MAX((g_cubfile_data.window_height / 2) - (projected_sprite_height / 2), 0);

	g_color = create_trgb(0, 0, 255, 0);
	while (*window_y < sprite_top_pixel)
	{
		draw_pixel(window_x, *window_y);
		(*window_y)++;
	}
}

// void	render_sprite_ray_basis(int window_x, int *window_y, const int projected_wall_height)
// {
// 	size_t			texture_offset_y;
// 	const int		wall_bottom_pixel = MIN((g_cubfile_data.window_height / 2) + (projected_wall_height / 2), g_cubfile_data.window_height);
// 	const t_texture texture = g_textures[g_rays[window_x].wall_hit_direction];
// 	const size_t	texture_offset_x = calc_texture_offset_x(g_rays[window_x], (float)texture.width);

// 	while (*window_y < wall_bottom_pixel)
// 	{
// 		texture_offset_y = calc_texture_offset_y(texture.height, projected_wall_height, *window_y);
// 		set_texture_color(texture, texture_offset_x, texture_offset_y);
// 		draw_pixel(window_x, *window_y);
// 		(*window_y)++;
// 	}
// }

int		calc_projected_sprite_height(size_t	index)
{
	float	normalized_angle_difference = calc_angle_difference_between_player_and_sprite(index);
	normalize_angle(&normalized_angle_difference);
	// これだと、中心への角度をもとにしているため、中心が視野に入っていない場合を弾いてしまう
	// if (fabs(normalized_angle_difference) > FOV_ANGLE / 2)
	// if (fabs(normalized_angle_difference) > 90 * (PI / 180))
	// 	return (0);
	const float perp_distance_to_project
		// = g_sprites[index].distance_from_player * cos(normalized_angle_difference);
		= fabs(g_sprites[index].distance_from_player * cos(normalized_angle_difference));
	// if (!cos(normalized_angle_difference))
	// 	return (0);

	// DI((int)index);
	// DF(normalized_angle_difference);
	// DF(cos(normalized_angle_difference));
	// DF(perp_distance_to_project);

	return ((int)(TILE_SIZE * (g_distance_proj_plane / perp_distance_to_project)));
	// return ((int)(g_distance_proj_plane * (TILE_SIZE / perp_distance_to_project)));
}

size_t	calc_sprite_texture_offset_x(t_ray_to_wall ray, float texture_width)
{
	const float texture_width_to_tile_size_ratio = texture_width / TILE_SIZE;
	const t_coord *wall_hit_coord = ray.wall_hit_coord;

	if (ray.was_hit_vertical)
		return (((size_t)wall_hit_coord->y % TILE_SIZE) * texture_width_to_tile_size_ratio);
	else
		return (((size_t)wall_hit_coord->x % TILE_SIZE) * texture_width_to_tile_size_ratio);
}

size_t	calc_sprite_texture_offset_y(int texture_height, const int projected_wall_height, int window_y)
{
	const size_t distance_from_wall_strip_top = (window_y + (projected_wall_height / 2)) - (g_cubfile_data.window_height / 2);

	return (distance_from_wall_strip_top * ((float)texture_height / projected_wall_height));
}

void	render_sprite(size_t index)
{
	const float	angle_difference_between_player_and_sprite = calc_angle_difference_between_player_and_sprite(index);
	if (angle_difference_between_player_and_sprite >= FOV_ANGLE || angle_difference_between_player_and_sprite <= -(FOV_ANGLE))
		return ;
	float	x_difference_between_window_center_and_sprite = (g_cubfile_data.window_width / FOV_ANGLE) * angle_difference_between_player_and_sprite;
	int		sprite_center_x = g_cubfile_data.window_width / 2 - (x_difference_between_window_center_and_sprite);

	int		projected_sprite_tile_size = calc_projected_sprite_height(index);

	// 正方形なのだから、以下は高さと幅に分ける必要はない。かなりきれいにまとめられるはず。
	const int assumed_sprite_top_pixel = (g_cubfile_data.window_height / 2) - (projected_sprite_tile_size / 2);
	const int sprite_top_pixel = MAX((g_cubfile_data.window_height / 2) - (projected_sprite_tile_size / 2), 0);
	const int		assumed_sprite_bottom_pixel = (g_cubfile_data.window_height / 2) + (projected_sprite_tile_size / 2);
	const int		sprite_bottom_pixel = MIN((g_cubfile_data.window_height / 2) + (projected_sprite_tile_size / 2), g_cubfile_data.window_height);
	const int sprite_height = assumed_sprite_bottom_pixel - assumed_sprite_top_pixel;
	const int		sprite_left_edge_pixel = sprite_center_x - projected_sprite_tile_size / 2;
	// const int		assumed_sprite_right_edge_pixel = sprite_center_x + projected_sprite_tile_size / 2;
	const int		sprite_right_edge_pixel = MIN(sprite_center_x + projected_sprite_tile_size / 2, g_cubfile_data.window_width);
	// const int sprite_width = assumed_sprite_right_edge_pixel - sprite_left_edge_pixel;
	const int sprite_width = sprite_height;

	int x = sprite_left_edge_pixel;
	// DI(sprite_center_x);
	// DI(projected_sprite_tile_size / 2);
	// DI(sprite_left_edge_pixel);
	// DI(sprite_right_edge_pixel);
	// ft_putchar('\n');
	while (x < sprite_right_edge_pixel)
	{
		if (x < 0)
			;
		else
		{
			int sprite_texture_offset_x = (int)((float)(x - sprite_left_edge_pixel) / sprite_width * g_textures[SPRITE].width);

			int y = sprite_top_pixel;
			while (y < sprite_bottom_pixel)
			{
				int sprite_texture_offset_y = (int)((float)(y - sprite_top_pixel) / sprite_height * g_textures[SPRITE].height);
				// DI(sprite_texture_offset_x);
				// DI(sprite_texture_offset_y);
				// g_color = create_trgb(0, 0, 0, 255);
				set_texture_color(g_textures[SPRITE], sprite_texture_offset_x, sprite_texture_offset_y);
				if (g_color)
				// create_trgb(0, 0, 0, 255);
					draw_pixel(x, y);
				y++;
			}
		}
		x++;
	}
}

// スプライト描写用の fix 以前
// void	render_sprite(size_t index)
// {
// 	const float	angle_difference_between_player_and_sprite = calc_angle_difference_between_player_and_sprite(index);
// 	float	x_difference_between_window_center_and_sprite = (g_cubfile_data.window_width / FOV_ANGLE) * angle_difference_between_player_and_sprite;
// 	int		sprite_center_x = g_cubfile_data.window_width / 2 - (x_difference_between_window_center_and_sprite);

// 	int		projected_sprite_tile_size = calc_projected_sprite_height(index);

// 	const int sprite_top_pixel = MAX((g_cubfile_data.window_height / 2) - (projected_sprite_tile_size / 2), 0);
// 	const int		sprite_bottom_pixel = MIN((g_cubfile_data.window_height / 2) + (projected_sprite_tile_size / 2), g_cubfile_data.window_height);
// 	const int		sprite_left_edge_pixel = sprite_center_x - projected_sprite_tile_size / 2;
// 	const int		sprite_right_edge_pixel = MIN(sprite_center_x + projected_sprite_tile_size / 2, g_cubfile_data.window_width);

// 	int x = sprite_left_edge_pixel;
// 	// DI(sprite_center_x);
// 	// DI(projected_sprite_tile_size / 2);
// 	// DI(sprite_left_edge_pixel);
// 	// DI(sprite_right_edge_pixel);
// 	// ft_putchar('\n');
// 	while (x < sprite_right_edge_pixel)
// 	{
// 		if (x < 0)
// 			;
// 		else
// 		{
// 			int y = sprite_top_pixel;
// 			g_color = create_trgb(0, 0, 255, 0);
// 			while (y < sprite_bottom_pixel)
// 			{
// 				draw_pixel(x, y);
// 				y++;
// 			}
// 		}
// 		x++;
// 	}
// }

void	test_draw_sprite_left_vertical_lines(void)
{
	size_t	index;

	index = 0;
	while (index < g_cubfile_data.sprites_num)
	{
		render_sprite(index);
		index++;
	}
}
// void	test_draw_sprite_left_vertical_lines(void)
// {
// 	size_t	index;

// 	index = 0;
// 	while (index < g_cubfile_data.sprites_num)
// 	{
// 		test_sprite_left_vertical_line(index);
// 		index++;
// 	}
// }
// void	calculate_size_to_project(size_t x)
// {
// 	const float	angle_difference_between_player_and_sprite = calc_angle_difference_between_player_and_sprite(index);
// 	float	perp_distance = g_sprites[0].distance_from_player * cos(angle_difference_between_player_and_sprite);
// 	const float	distance_proj_plane = (g_cubfile_data.window_width / 2) / tan(FOV_ANGLE / 2);
// 	float	projected_h = (TILE_SIZE / perp_distance) * distance_proj_plane;
// 	float	strip_h = projected_h;
// 	float	top_pixel = MAX(g_cubfile_data.window_height / 2 - strip_h / 2, 0);
// 	float	bottom_pixel = MIN(g_cubfile_data.window_height / 2 + strip_h / 2, g_cubfile_data.window_height);

// 	const float	angle_difference_between_player_and_sprite = calc_angle_difference_between_player_and_sprite(index);
// 	float	x_difference_from_center = (g_cubfile_data.window_width / FOV_ANGLE) * angle_difference_between_player_and_sprite;
// 	float	start_render_x = g_cubfile_data.window_width / 2 - x_difference_from_center;
// 	float	sprite_screen_left_x = start_render_x - strip_h / 2;
// 	float	texture_offset_x = (TILE_SIZE / 2) * (g_textures[SPRITE].width / TILE_SIZE);

// 	while (start_render_x >= sprite_screen_left_x)
// 	{
// 		if (start_render_x < 0)
// 			break ;
// 		if (start_render_x < g_cubfile_data.window_width)
// 		texture_offset_x -= ((float)TILE_SIZE / (float));
// 	}
// }

// void	hoge(void)
// {
// 	size_t	x;

// 	x = 0;
// 	while (x < g_cubfile_data.window_width)
// 	{
// 		calculate_size_to_project(x);
// 		x++;
// 	}
// }

void	update(void)
{
	move_player();
	reset_sprites_texture_data();
	// record_sprites_within_fov();
	cast_all_rays_to_wall();
	// test_sprite_hit();
	// cast_all_rays();
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
	test_draw_sprite_left_vertical_lines();
	render_mini_map();
	render_rays();
	sprites();
	render_player();

	// DF(calc_angle_difference_between_player_and_sprite(0));
	// test_draw_sprite_center_vertical_lines();
	// size_t	index = 0;
	// while (index < g_cubfile_data.sprites_num)
	// {
	// 	draw_sprite_center_column(index);
	// 	index++;
	// }
	// draw_green_line_vertically(1);

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