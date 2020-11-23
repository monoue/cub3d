/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_to_sprite.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 15:39:15 by monoue            #+#    #+#             */
/*   Updated: 2020/11/24 07:47:43 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// TODO: このファイルまるごと要らないかも
#include "ray_to_sprite.h"

t_ray_to_wall	g_rays_to_sprite[MAX_WINDOW_WIDTH];

t_coord	*adjust_coord_to_tile_center(t_coord *coord)
{
	t_coord	*coord_adjusted;
	const int	center_x = floor(coord->x / TILE_SIZE) * TILE_SIZE + TILE_SIZE * 0.5;
	const int	center_y = floor(coord->y / TILE_SIZE) * TILE_SIZE + TILE_SIZE * 0.5;

	coord_adjusted = malloc(sizeof(coord_adjusted));
	coord_assign(coord_adjusted, center_x, center_y);
	// coord_int->x = malloc(sizeof(int));
	// coord_int->y = malloc(sizeof(int));
	// coord_adjusted->x = center_x;
	// coord_adjusted->y = center_y;
	return (coord_adjusted);
}

void	record_sprite_hit(t_coord *to_check_coord)
{
	size_t	index;
	// const t_coord_int	*to_check_coord_int = adjust_coord_to_tile_center(to_check_coord);
	const t_coord	*tile_center_coord = adjust_coord_to_tile_center(to_check_coord);

	index = 0;
	while (index < g_cubfile_data.sprites_num)
	{
		// DF(g_sprites[index].x);
		// DF(tile_center_coord->x);
		// DF(g_sprites[index].y);
		// DF(tile_center_coord->y);
		if (g_sprites[index].x == tile_center_coord->x && g_sprites[index].y == tile_center_coord->y)
		{
			g_sprites[index].is_visible = true;
			break ;
		}
		index++;
	}
}

// この関数、蛇足かも
// char	get_map_at(size_t y, size_t x)
// {
// 	return (g_map[y][x]);
// }
// from_zero ver.
// float	normalize_angle(float angle)
// {
// 	float normalized_angle;

// 	normalized_angle = remainder(angle, TWO_PI);
// 	if (normalized_angle < 0)
// 		normalized_angle += TWO_PI;
// 	return (normalized_angle);
// }

// float	distance_between_points(float x1, float y1, float x2, float y2)
// {
// 	const float	x_diff = x2 - x1;
// 	const float	y_diff = y2 - y1;

// 	return (sqrt(pow(x_diff, 2) + pow(y_diff, 2)));
// }

// bool	is_inside_map(t_coord *coord)
// {
// 	const float		x = coord->x;
// 	const float		y = coord->y;
// 	const size_t	edge = MAX_MAP_LEN * TILE_SIZE;

//     return (x >= 0 && x <= edge && y >= 0 && y <= edge);
// }

// static void	set_ray_direction(t_textures_num *direction, bool was_hit_vertical, bool is_ray_facing_right, bool is_ray_facing_down)
// {
// 	if (was_hit_vertical)
// 	{
// 		if (is_ray_facing_right)
// 			*direction = EAST;
// 		else
// 			*direction = WEST;
// 	}
// 	else
// 	{
// 		if (is_ray_facing_down)
// 			*direction = SOUTH;
// 		else
// 			*direction = NORTH;
// 	}
// }

// bool is_ray_facing_down(float angle)
// {
// 	return (angle > 0 && angle < PI);
// }

// bool is_ray_facing_up(float angle)
// {
// 	return (!is_ray_facing_down(angle));
// }

// bool is_ray_facing_right(float angle)
// {
// 	return (angle < HALF_PI || angle > PI + HALF_PI);
// }

// bool is_ray_facing_left(float angle)
// {
// 	return (!is_ray_facing_right(angle));
// }

// float	get_hit_distance(t_coord *wall_hit_coord, bool is_hit_found)
// {
// 	float	hit_distance;

// 	if (is_hit_found == true)
// 		hit_distance = distance_between_points(g_player.x, g_player.y, wall_hit_coord->x, wall_hit_coord->y);
// 	else
// 		hit_distance = FLT_MAX;
// 	return (hit_distance);
// }

// void	init_horz_hitter_step(t_coord *step, float ray_angle)
// {
// 	step->y = is_ray_facing_down(ray_angle) ? TILE_SIZE : -(TILE_SIZE);
// 	step->x = TILE_SIZE / tan(ray_angle);
// 	if ((is_ray_facing_left(ray_angle) && step->x > 0) || (is_ray_facing_right(ray_angle) && step->x < 0))
// 		step->x *= -1;
// }

// void	init_horz_hitter_intercept(t_coord *intercept, float ray_angle)
// {
// 	intercept->y = floor(g_player.y / TILE_SIZE) * TILE_SIZE;
// 	if (is_ray_facing_down(ray_angle))
// 		intercept->y += TILE_SIZE;
// 	intercept->x = g_player.x + (intercept->y - g_player.y) / tan(ray_angle);
// }

void	seek_horizontal_hit(t_ray_materials *horz_hitter, float ray_angle)
{
	horz_hitter->is_wall_hit_found = false;
	coord_assign(horz_hitter->wall_hit_coord, 0, 0);
	init_horz_hitter_intercept(horz_hitter->intercept, ray_angle);
	init_horz_hitter_step(horz_hitter->step, ray_angle);
	coord_copy(horz_hitter->next_touch_coord, horz_hitter->intercept);
	while (is_inside_map(horz_hitter->next_touch_coord) == true)
	{
		coord_copy(horz_hitter->to_check_coord, horz_hitter->next_touch_coord);
		if (is_ray_facing_up(ray_angle))
			horz_hitter->to_check_coord->y--;
		if (map_has_wall_at(horz_hitter->to_check_coord->x, horz_hitter->to_check_coord->y) == true)
		{
			coord_copy(horz_hitter->wall_hit_coord, horz_hitter->next_touch_coord);
			// horz->wall_content = get_map_at(horz->to_check_coord);
			horz_hitter->is_wall_hit_found = true;
			break;
		}
		coord_add(horz_hitter->next_touch_coord, horz_hitter->step);
	}
	horz_hitter->hit_distance = get_hit_distance(horz_hitter->wall_hit_coord, horz_hitter->is_wall_hit_found);
}


// void	init_vert_hitter_step(t_coord *step, float ray_angle)
// {
// 	step->x = is_ray_facing_right(ray_angle) ? TILE_SIZE : -(TILE_SIZE);
// 	step->y = TILE_SIZE * tan(ray_angle);
// 	if ((is_ray_facing_down(ray_angle) && step->y < 0) || (is_ray_facing_up(ray_angle) && step->y > 0))
// 		step->y *= -1;
// }

// void	init_vert_hitter_intercept(t_coord *intercept, float ray_angle)
// {
// 	intercept->x = floor(g_player.x / TILE_SIZE) * TILE_SIZE;
// 	if (is_ray_facing_right(ray_angle))
// 		intercept->x += TILE_SIZE;
// 	intercept->y = g_player.y + (intercept->x - g_player.x) * tan(ray_angle);
// }

void	seek_vertical_hit(t_ray_materials *vert_hitter, float ray_angle)
{
	size_t	sprite_i;

	coord_assign(vert_hitter->wall_hit_coord, 0, 0);
	init_vert_hitter_intercept(vert_hitter->intercept, ray_angle);
	init_vert_hitter_step(vert_hitter->step, ray_angle);
	coord_copy(vert_hitter->next_touch_coord, vert_hitter->intercept);
	while (is_inside_map(vert_hitter->next_touch_coord) == true && map_has_wall_at(vert_hitter->next_touch_coord->x, vert_hitter->next_touch_coord->y) == false)
	{
		coord_copy(vert_hitter->to_check_coord, vert_hitter->next_touch_coord);
		if (is_ray_facing_left(ray_angle))
			vert_hitter->to_check_coord->x--;
		if (map_has_sprite_at(vert_hitter->to_check_coord->x, vert_hitter->to_check_coord->y) == true)
		{
			// TODO: ここは関数として切り出しちゃって良い。多分、もう一つの方でも再利用できる。
			// TODO: 真ん中の座標を求める。sprite.c 内の、set_sprite_data の処理を使う。
			sprite_i = 0;
			while (sprite_i < g_cubfile_data.sprites_num)
			{
				sprite_i++;
			}
			// 真ん中の座標が一致したら hit したというフラグをその sprite の構造体に立てて、break。
		}
		coord_add(vert_hitter->next_touch_coord, vert_hitter->step);
	}
	// TODO: update ごとに、構造体全部のループを回して、is_visible を初期化し直すのを忘れずに！
}

t_ray_materials	*malloc_t_ray_materials()
{
	t_ray_materials	*ray_materials;

	ray_materials = malloc(sizeof(t_ray_materials));
	ray_materials->intercept = malloc(sizeof(t_coord));
	ray_materials->step = malloc(sizeof(t_coord));
	ray_materials->wall_hit_coord = malloc(sizeof(t_coord));
	ray_materials->next_touch_coord = malloc(sizeof(t_coord));
	ray_materials->to_check_coord = malloc(sizeof(t_coord));
	return (ray_materials);
}

void	free_each_t_ray_materials(t_ray_materials *ray_materials)
{
	free(ray_materials->intercept);
	free(ray_materials->step);
	free(ray_materials->wall_hit_coord);
	free(ray_materials->next_touch_coord);
	free(ray_materials->to_check_coord);
	free(ray_materials);
}

void	free_t_ray_materials(t_ray_materials *struct1, t_ray_materials *struct2)
{
	free_each_t_ray_materials(struct1);
	free_each_t_ray_materials(struct2);
}

void	cast_ray_to_count_visible_sprites(float ray_angle, size_t strip_id)
{
	t_ray_materials	*horz_hitter;
	t_ray_materials	*vert_hitter;

	horz_hitter = malloc_t_ray_materials();
	vert_hitter = malloc_t_ray_materials();
	seek_horizontal_hit(horz_hitter, ray_angle);
	seek_vertical_hit(vert_hitter, ray_angle);
	// TODO: wall_hit_coord, 最後に free
	// g_rays[strip_id].wall_hit_coord = malloc(sizeof(t_coord));


	// ここは最後の、記録部分。初回チェックの際は要らない。
	// if (vert_hitter->hit_distance < horz_hitter->hit_distance)
	// {
	// 	g_rays[strip_id].distance = vert_hitter->hit_distance;
	// 	coord_copy(g_rays[strip_id].wall_hit_coord, vert_hitter->wall_hit_coord);
	// 	// g_rays[strip_id].wall_hit_content = vert->wall_content;
	// 	g_rays[strip_id].was_hit_vertical = true;
	// }
	// else
	// {
	// 	g_rays[strip_id].distance = horz_hitter->hit_distance;
	// 	coord_copy(g_rays[strip_id].wall_hit_coord, horz_hitter->wall_hit_coord);
	// 	// g_rays[strip_id].wall_hit_content = horz->wall_content;
	// 	g_rays[strip_id].was_hit_vertical = false;
	// }
	// set_ray_direction(&g_rays[strip_id].wall_hit_direction, g_rays[strip_id].was_hit_vertical, is_ray_facing_right(ray_angle), is_ray_facing_down(ray_angle));
	// g_rays[strip_id].ray_angle = ray_angle;
	free_t_ray_materials(horz_hitter, vert_hitter);
}
