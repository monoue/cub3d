/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:12:21 by monoue            #+#    #+#             */
/*   Updated: 2020/11/11 14:47:51 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

// t_ray	rays[g_cubfile_data.window_width];
// t_ray	rays[NUM_RAYS];
t_ray	rays[MAX_WINDOW_WIDTH];

void	normalize_angle(float *angle)
{
	*angle = remainder(*angle, TWO_PI);
	if (*angle < 0)
		*angle += TWO_PI;
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

float	distance_between_points(float x1, float y1, float x2, float y2)
{
	const float	x_diff = x2 - x1;
	const float	y_diff = y2 - y1;

	return (sqrt(pow(x_diff, 2) + pow(y_diff, 2)));
}

bool is_out_of_window(float x, float y) {
	return (x < 0 || x >= MAX_MAP_LEN * TILE_SIZE || y < 0 || y >= MAX_MAP_LEN * TILE_SIZE);
}

// bool is_inside_map(float x, float y) {
// 	return (x >= 0 && x < MAX_MAP_LEN * TILE_SIZE && y >= 0 && y < MAX_MAP_LEN * TILE_SIZE);
// }

bool	is_inside_map(t_coord *coord)
{
	const float		x = coord->x;
	const float		y = coord->y;
	const size_t	edge = MAX_MAP_LEN * TILE_SIZE;

    return (x >= 0 && x <= edge && y >= 0 && y <= edge);
}

static void	set_ray_direction(t_textures *direction, bool was_hit_vertical, bool is_ray_facing_right, bool is_ray_facing_down)
{
	if (was_hit_vertical)
	{
		if (is_ray_facing_right)
			*direction = EAST;
		else
			*direction = WEST;
	}
	else
	{
		if (is_ray_facing_down)
			*direction = SOUTH;
		else
			*direction = NORTH;
	}
}

bool is_ray_facing_down(float angle)
{
	return (angle > 0 && angle < PI);
}

bool is_ray_facing_up(float angle)
{
	return (!is_ray_facing_down(angle));
}

bool is_ray_facing_right(float angle)
{
	return (angle < HALF_PI || angle > PI + HALF_PI);
}

bool is_ray_facing_left(float angle)
{
	return (!is_ray_facing_right(angle));
}

// float	get_hit_distance(float wall_hit_x, float wall_hit_y, bool is_hit_found)
float	get_hit_distance(t_coord *wall_hit, bool is_hit_found)
{
	float	hit_distance;

	if (is_hit_found == true)
		hit_distance = distance_between_points(g_player.x, g_player.y, wall_hit->x, wall_hit->y);
	else
		hit_distance = FLT_MAX;
	return (hit_distance);
}

float	init_parallel_step(float ray_angle, t_axes axis)
{
	float	step;

	if (axis == HORIZONTAL)
	{
		step = TILE_SIZE / tan(ray_angle);
		if ((is_ray_facing_left(ray_angle) && step > 0) || (is_ray_facing_right(ray_angle) && step < 0))
			step *= -1;
	}
	else
	{
		step = TILE_SIZE * tan(ray_angle);
		if ((is_ray_facing_down(ray_angle) && step < 0) || (is_ray_facing_up(ray_angle) && step > 0))
			step *= -1;
	}
	return (step);
}

t_coord	*coord_assign(t_coord *dst, float x, float y)
{
	dst->x = x;
	dst->y = y;
	return (dst);
}

t_coord	*coord_copy(t_coord *dst, t_coord *src)
{
	coord_assign(dst, src->x, src->y);
	return (dst);
}

t_coord	*coord_add(t_coord *dst, t_coord *add)
{
	coord_assign(dst, dst->x + add->x, dst->y + add->y);
	return (dst);
}


// 構造体作るしかなさそう（intercept, step, wall_hit）
// axes から名前変えた方がいいかも。なぜなら、構造体のメンバそれぞれ、[2] にして X と Y で使った方が良さそうで、それこそ axes だから。
// TODO: これでうまく行かなければ、構造体メンバの x と y はポインタで渡す
t_ray_materials	cast_ray_horizontal(t_ray_materials *horz, float ray_angle, size_t strip_id)
{
	horz->is_wall_hit_found = false;
	coord_assign(horz->wall_hit, 0, 0);
	horz->intercept->y = floor(g_player.y / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_down(ray_angle))
		horz->intercept->y += TILE_SIZE;
	horz->intercept->x = g_player.x + (horz->intercept->y - g_player.y) / tan(ray_angle);
	horz->step->y = is_ray_facing_down(ray_angle) ? TILE_SIZE : -(TILE_SIZE);
	horz->step->x = init_parallel_step(ray_angle, HORIZONTAL);
	coord_copy(horz->next_touch, horz->intercept);
	while (is_inside_map(horz->next_touch) == true)
	{
		coord_copy(horz->to_check, horz->next_touch);
		if (is_ray_facing_up(ray_angle))
			horz->to_check->y--;
		if (map_has_wall_at(horz->to_check) == true)
		{
			coord_copy(horz->wall_hit, horz->next_touch);
			horz->wall_content = get_map_at(horz->to_check);
			horz->is_wall_hit_found = true;
			break;
		}
		coord_add(horz->next_touch, horz->step);
	}
	horz->hit_distance = get_hit_distance(horz->wall_hit, horz->is_wall_hit_found);
}

char	get_map_at(t_coord *coord)
{
	const int x = (int)(coord->x / TILE_SIZE);
	const int y = (int)(coord->y / TILE_SIZE);

	return (g_map[y][x]);
}

t_ray_materials	cast_ray_vertical(t_ray_materials *vert, float ray_angle, size_t strip_id)
{
	vert->is_wall_hit_found = false;
	coord_assign(vert->wall_hit, 0, 0);
	vert->intercept->x = floor(g_player.x / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_right(ray_angle))
		vert->intercept->x += TILE_SIZE;
	vert->intercept->y = g_player.y + (vert->intercept->x - g_player.x) * tan(ray_angle);
	vert->step->x = is_ray_facing_right(ray_angle) ? TILE_SIZE : -(TILE_SIZE);
	vert->step->y = init_parallel_step(ray_angle, VERTICAL);
	coord_copy(vert->next_touch, vert->intercept);
	while (is_inside_map(vert->next_touch) == true)
	{
		coord_copy(vert->to_check, vert->next_touch);
		if (is_ray_facing_left(ray_angle))
			vert->to_check->x--;
		if (map_has_wall_at(vert->to_check) == true)
		{
			coord_copy(vert->wall_hit, vert->next_touch);
			vert->wall_content = get_map_at(vert->to_check);
			vert->is_wall_hit_found = true;
			break;
		}
		coord_add(vert->next_touch, vert->step);
	}
	vert->hit_distance = get_hit_distance(vert->wall_hit, vert->is_wall_hit_found);
}

void	cast_ray(float ray_angle, size_t strip_id)
{
	t_ray_materials	horz;
	t_ray_materials	vert;

	cast_ray_horizontal(&horz, ray_angle, strip_id);
	cast_ray_vertical(&vert, ray_angle, strip_id);
	if (vert.hit_distance < horz.hit_distance)
	{
		rays[strip_id].distance = vert.hit_distance;
		// assign 使うべき

		rays[strip_id].wall_hit.x = vert->wall_hit->x;
		rays[strip_id].wall_hit.y = *(vert->wall_hit->y);
		rays[strip_id].wall_hit_content = vert.wall_content;
		rays[strip_id].was_hit_vertical = true;

		// rays[strip_id].distance = vert_hit_distance;
		// rays[strip_id].wall_hit.x = vert_wall_hit_x;
		// rays[strip_id].wall_hit.y = vert_wall_hit_y;
		// rays[strip_id].wall_hit_content = vert_wall_content;
		// rays[strip_id].was_hit_vertical = true;
	}
	else
	{
		rays[strip_id].distance = horz_hit_distance;
		rays[strip_id].wall_hit.x = horz_wall_hit_x;
		rays[strip_id].wall_hit.y = horz_wall_hit_y;
		rays[strip_id].wall_hit_content = horz_wall_content;
		rays[strip_id].was_hit_vertical = false;

		// rays[strip_id].distance = horz_hit_distance;
		// rays[strip_id].wall_hit.x = horz_wall_hit_x;
		// rays[strip_id].wall_hit.y = horz_wall_hit_y;
		// rays[strip_id].wall_hit_content = horz_wall_content;
		// rays[strip_id].was_hit_vertical = false;
	}
	set_ray_direction(&rays[strip_id].direction, rays[strip_id].was_hit_vertical, is_ray_facing_right(ray_angle), is_ray_facing_down(ray_angle));
	rays[strip_id].ray_angle = ray_angle;
	// DI(rays[strip_id].direction);
}

void	cast_all_rays()
{
	float	ray_angle;
	size_t	strip_id;

	ray_angle = g_player.rotation_angle - (FOV_ANGLE / 2);
	strip_id = 0;
	while (strip_id < (size_t)g_cubfile_data.window_width)
	{
		normalize_angle(&ray_angle);
		cast_ray(ray_angle, strip_id);
		ray_angle += FOV_ANGLE / g_cubfile_data.window_width;
		strip_id++;
	}
}

void	render_rays(void)
{
	size_t	index;

	index = 0;
	g_color = create_trgb(200, 255, 241, 0);
	while (index < (size_t)g_cubfile_data.window_width)
	{
		draw_line
		(
			g_player.x * MINIMAP_SCALE_FACTOR,
			g_player.y * MINIMAP_SCALE_FACTOR,
			rays[index].wall_hit_x * MINIMAP_SCALE_FACTOR,
			rays[index].wall_hit_y * MINIMAP_SCALE_FACTOR
		);
		index++;
	}
	// test_ray_data(0);
	// test_ray_data(NUM_RAYS - 1);
}