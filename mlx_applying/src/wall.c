#include "wall.h"

void	change_color_intensity(t_color *color, float factor)
{
	t_color	a;
	t_color	r;
	t_color	g;
	t_color	b;

	a = (*color & 0xFF000000);
	r = (*color & 0x00FF0000) * factor;
	g = (*color & 0x0000FF00) * factor;
	b = (*color & 0x000000FF) * factor;
	*color = a | (r & 0x00FF0000) | (g & 0x0000FF00) | (b & 0x000000FF);
}

void	render_wall_projection(void)
{
	int		ray_i;
	int		wall_strip_height;
	float	projected_wall_height;
	int		wall_top_pixel;
	int		wall_bottom_pixel;
	int		y;
	float	correct_distance;
	int		texture_offset_x;
	int		texture_offset_y;
	uint32_t	texel_color;
	int		distance_from_top;
	int		texture_width;
	int		texture_height;

	ray_i = 0;
	while (ray_i < NUM_RAYS)
	{
		correct_distance = rays[ray_i].distance * cos(rays[ray_i].ray_angle - g_player.rotation_angle);
		// 三角形の相似で縮小。TILE_SIZE は、実際の壁の高さ。
		projected_wall_height = (TILE_SIZE / correct_distance) * DIST_PROJ_PLANE;
		wall_strip_height = (int)projected_wall_height;
		wall_top_pixel = (WINDOW_HEIGHT / 2) - (wall_strip_height / 2);
		if (wall_top_pixel < 0)
			wall_top_pixel = 0;
		wall_bottom_pixel = (WINDOW_HEIGHT / 2) + (wall_strip_height / 2);
		if (wall_bottom_pixel > WINDOW_HEIGHT)
			wall_bottom_pixel = WINDOW_HEIGHT;
		y = 0;
		while (y < wall_top_pixel)
		{
			draw_pixel(ray_i, y, 0xFF444444);
			y++;
		}

		if (rays[ray_i].was_hit_vertical)
			texture_offset_x = (int)rays[ray_i].wall_hit_y % TILE_SIZE;
		else
			texture_offset_x = (int)rays[ray_i].wall_hit_x % TILE_SIZE;

		int	texNum;

		texNum =  rays[ray_i].wall_hit_content - 1;
		texture_width = wall_textures[texNum].width;
		texture_height = wall_textures[texNum].height;

		while (y < wall_bottom_pixel)
		{
			distance_from_top = y + (wall_strip_height / 2) - (WINDOW_HEIGHT / 2);
			texture_offset_y = distance_from_top * ((float)texture_height / wall_strip_height);

			// set the color of the wall based on the color from the texture
			texel_color = wall_textures[texNum].texture_buffer[(texture_width * texture_offset_y) + texture_offset_x];

			if (rays[ray_i].was_hit_vertical)
				change_color_intensity(&texel_color, 0.7);
			// texel_color = textures[texNum][(texture_width * texture_offset_y) + texture_offset_x];
			draw_pixel(ray_i, y, texel_color);
			// colorBuffer[(WINDOW_WIDTH * y) + ray_i] = texel_color;
			y++;
		}
		while (y < WINDOW_HEIGHT)
		{
			draw_pixel(ray_i, y, 0xFF888888);
			y++;
		}

		ray_i++;
	}

}