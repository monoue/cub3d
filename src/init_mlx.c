/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 10:13:55 by monoue            #+#    #+#             */
/*   Updated: 2020/11/11 14:26:10 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_mlx.h"

#include "test.h"

t_mlx	g_mlx;
t_img	g_img;

// t_color	*color_buffer = NULL;

// t_color	*color_buffer_texture;

// TODO: 多分要らない
t_color	*wall_texture = NULL;






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
			else if (g_map[y_i][x_i] == '2')
				g_color = create_trgb(0, 155, 155, 155);
			else
				g_color = create_trgb(0, 0, 0, 0);
			draw_rectangle(
				floor(tile_x * MINIMAP_SCALE_FACTOR),
				floor(tile_y * MINIMAP_SCALE_FACTOR),
				ceil(TILE_SIZE * MINIMAP_SCALE_FACTOR),
				ceil(TILE_SIZE * MINIMAP_SCALE_FACTOR)
			);
			x_i++;
		}
		y_i++;
	}
}


bool	map_has_wall_at(t_coord *coord)
{
	int grid_x;
	int grid_y;

	grid_x = floor(coord->x / TILE_SIZE);
	grid_y = floor(coord->y / TILE_SIZE);
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

void	render_rays_to_sprites()
{
	size_t			index;
	const size_t	s_num = g_cubfile_data.sprites_num;

	index = 0;
	while (index < s_num)
	{
		g_color = create_trgb(0, floor(255 * index / (s_num - 1)), 50, floor(255 - 255 * (index / (s_num - 1))));
		draw_line(
			g_player.x * MINIMAP_SCALE_FACTOR,
			g_player.y * MINIMAP_SCALE_FACTOR,
			g_sprites[index].x * MINIMAP_SCALE_FACTOR,
			g_sprites[index].y * MINIMAP_SCALE_FACTOR);
		index++;
	}
}

void	set_distance_to_sprite(size_t index)
{
	float	delta_x;
	float	delta_y;

	delta_x = g_sprites[index].x - g_player.x;
	delta_y = g_sprites[index].y - g_player.y;
	g_sprites[index].distance = sqrt(pow(delta_x, 2) + pow(delta_x, 2));
}

void	update_distances_to_sprites(void)
{
	size_t	index;

	index = 0;
	while (index < g_cubfile_data.sprites_num)
	{
		set_distance_to_sprite(index);
		index++;
	}
}

void	sort_sprites(void)
{
	size_t		index;
	size_t		inner_i;
	t_sprite	tmp;

	index = 0;
	while (index < g_cubfile_data.sprites_num - 1)
	{
		inner_i = index + 1;
		while (inner_i < g_cubfile_data.sprites_num)
		{
			if (g_sprites[index].distance < g_sprites[inner_i].distance)
			{
				tmp = g_sprites[index];
				g_sprites[index] = g_sprites[inner_i];
				g_sprites[inner_i] = tmp;
			}
			inner_i++;
		}
		index++;
	}
}

void	sprites(void)
{
	update_distances_to_sprites();
	sort_sprites();
	render_rays_to_sprites();
}

int	main_loop(void *null)
{
	(void)null;
	update();
	g_color = create_trgb(0, 0, 0, 0);
	draw_rectangle(0, 0, g_cubfile_data.window_width, g_cubfile_data.window_height);
	render_wall_projection();
	render_map();
	render_rays();
	sprites();
	render_player();
	mlx_put_image_to_window(g_mlx.mlx_ptr, g_mlx.win_ptr, g_img.img_ptr, 0, 0);
	mlx_do_sync(g_mlx.mlx_ptr);
	return (0);
}

// void	setup()
// {
// 	wall_texture = malloc(sizeof(t_color) * (t_color)g_cubfile_data.window_width * (t_color)g_cubfile_data.window_height);
// 	size_t	x;
// 	size_t	y;
// 	y = 0;
// 	while (y < TILE_SIZE)
// 	{
// 		x = 0;
// 		while (x < TILE_SIZE)
// 		{
// 			wall_texture[(TILE_SIZE * y) + x] = ((x % 6 && y % 8) ? create_trgb(0, 200, 100, 100) : create_trgb(0, 200, 50, 50));
// 			x++;
// 		}
// 		y++;
// 	}
// }

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