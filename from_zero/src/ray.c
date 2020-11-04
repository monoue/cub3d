/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:12:21 by monoue            #+#    #+#             */
/*   Updated: 2020/11/04 10:49:42 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_ray	rays[NUM_RAYS];

void	normalize_angle(float *angle)
{
	*angle = remainder(*angle, TWO_PI);
	if (*angle < 0)
		*angle += TWO_PI;
}

char	get_map_at(size_t y, size_t x)
{
	return (g_map[y][x]);
}
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

bool is_inside_map(float x, float y) {

	return (x >= 0 && x <= g_cubfile_data.window_width && y >= 0 && y <= g_cubfile_data.window_height);
    // return (x >= 0 && x <= MAP_NUM_COLS * TILE_SIZE && y >= 0 && y <= MAP_NUM_ROWS * TILE_SIZE);
}
// mlx_applying ver.
void	cast_ray(float ray_angle, int stripId)
{
	normalize_angle(&ray_angle);

	bool	is_ray_facing_down = (ray_angle > 0 && ray_angle < PI);
	bool	is_ray_facing_up = !is_ray_facing_down;
	bool	is_ray_facing_right = ((ray_angle < 0.5 * PI) || (ray_angle > 1.5 * PI));
	bool	is_ray_facing_left = !is_ray_facing_right;
	float	xintercept;
	float	yintercept;
	float	xstep;
	float	ystep;
	// ///////////////////////////////////////////
	// // HORIZONTAL RAY-GRID INTERSECTION CODE //
	// ///////////////////////////////////////////
	bool	found_horz_wall_hit = false;
	float	horz_wall_hit_x = 0;
	float	horz_wall_hit_y = 0;
	int		horz_wall_content = 0;
	// Find the y-coordinate of the closest horizontal grid intersection
	yintercept = floor(g_player.y / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_down)
		yintercept += TILE_SIZE;

	// Find the x-coordinate of the closest horizontal grid intersection
	xintercept = g_player.x + (yintercept - g_player.y) / tan(ray_angle);

	// Calculate the increment xstep and y step
	ystep = is_ray_facing_down ? TILE_SIZE : -(TILE_SIZE);

	xstep = TILE_SIZE / tan(ray_angle);
	if ((is_ray_facing_left && xstep > 0) || (is_ray_facing_right && xstep < 0))
		xstep *= -1;
	float	next_horz_touch_x = xintercept;
	float	next_horz_touch_y = yintercept;
	// increment xstep and ystep until we find a wall
	while (is_inside_map(next_horz_touch_x, next_horz_touch_y))
	{
		float	x_to_check;
		float	y_to_check;

		x_to_check = next_horz_touch_x;
		y_to_check = next_horz_touch_y;
		if (is_ray_facing_up)
			y_to_check--;
		if (map_has_wall_at(x_to_check, y_to_check))
		{
			horz_wall_hit_x = next_horz_touch_x;
			horz_wall_hit_y = next_horz_touch_y;
			horz_wall_content = get_map_at((int)floor(y_to_check / TILE_SIZE), (int)floor(x_to_check / TILE_SIZE));
			found_horz_wall_hit = true;
			break;
		}
		next_horz_touch_x += xstep;
		next_horz_touch_y += ystep;
	}
	// ///////////////////////////////////////////
	// // VERTICAL RAY-GRID INTERSECTION CODE //
	// ///////////////////////////////////////////
	bool	found_vert_wall_hit = false;
	float	vert_wall_hit_x = 0;
	float	vert_wall_hit_y = 0;
	int		vert_wall_content = 0;

	// Find the x-coordinate of the closest vertical grid intersection
	xintercept = floor(g_player.x / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_right)
		xintercept += TILE_SIZE;
	// Find the y-coordinate of the closest vertical grid intersection
	yintercept = g_player.y + (xintercept - g_player.x) * tan(ray_angle);
	// Calculate the increment xstep and y step
	xstep = is_ray_facing_right ? TILE_SIZE : -(TILE_SIZE);

	ystep = TILE_SIZE * tan(ray_angle);
	if ((is_ray_facing_down && ystep < 0) || (is_ray_facing_up && ystep > 0))
		ystep *= -1;

	float	next_vert_touch_x = xintercept;
	float	next_vert_touch_y = yintercept;

	// increment xstep and ystep until we find a wall
    while (is_inside_map(next_vert_touch_x, next_vert_touch_y))
	{
		float	x_to_check;
		float	y_to_check;

		x_to_check = next_vert_touch_x;
		y_to_check = next_vert_touch_y;
		if (is_ray_facing_left)
			x_to_check--;
		if (map_has_wall_at(x_to_check, y_to_check))
		{
			vert_wall_hit_x = next_vert_touch_x;
			vert_wall_hit_y = next_vert_touch_y;
			vert_wall_content = get_map_at((int)floor(y_to_check / TILE_SIZE), (int)floor(x_to_check / TILE_SIZE));
			found_vert_wall_hit = true;
			break;
		}
		next_vert_touch_x += xstep;
		next_vert_touch_y += ystep;
	}
	// const float	horzHitDistance = (found_horz_wall_hit)
	float	horz_hit_distance = (found_horz_wall_hit)
		? distance_between_points(g_player.x, g_player.y, horz_wall_hit_x, horz_wall_hit_y)
		: FLT_MAX;
	// const float	vert_hit_distance = (found_vert_wall_hit)
	float	vert_hit_distance = (found_vert_wall_hit)
		? distance_between_points(g_player.x, g_player.y, vert_wall_hit_x, vert_wall_hit_y)
		: FLT_MAX;
	if (vert_hit_distance < horz_hit_distance)
	{
		rays[stripId].distance = vert_hit_distance;
		rays[stripId].wall_hit_x = vert_wall_hit_x;
		rays[stripId].wall_hit_y = vert_wall_hit_y;
		rays[stripId].wall_hit_content = vert_wall_content;
		rays[stripId].was_hit_vertical = true;
	}
	else
	{
		rays[stripId].distance = horz_hit_distance;
		rays[stripId].wall_hit_x = horz_wall_hit_x;
		rays[stripId].wall_hit_y = horz_wall_hit_y;
		rays[stripId].wall_hit_content = horz_wall_content;
		rays[stripId].was_hit_vertical = false;
	}
	rays[stripId].ray_angle = ray_angle;
}

// from_zero ver.
// void	cast_ray(float original_ray_angle, size_t strip_id)
// {
// 	float	ray_angle;

// 	ray_angle = normalize_angle(original_ray_angle);
// 	bool	is_ray_facing_down = ray_angle > 0 && ray_angle < PI;
// 	bool	is_ray_facing_up = !is_ray_facing_down;
// 	bool	is_ray_facing_right = ray_angle < HALF_PI || ray_angle > PI + HALF_PI;
// 	bool	is_ray_facing_left = !is_ray_facing_right;

// 	float	x_intercept;
// 	float	y_intercept;
// 	float	x_step;
// 	float	y_step;

// 	/////////////////////
// 	// HORIZONTAL PART //
// 	/////////////////////
// 	int	found_horz_wall_hit;
// 	found_horz_wall_hit = false;
// 	float	horz_wall_hit_x;
// 	float	horz_wall_hit_y;
// 	horz_wall_hit_x = 0;
// 	horz_wall_hit_y = 0;
// 	char	horz_wall_content;

// 	y_intercept = floor(g_player.y / TILE_SIZE) * TILE_SIZE;
// 	if (is_ray_facing_down)
// 		y_intercept += TILE_SIZE;
// 	x_intercept = g_player.x + (y_intercept - g_player.y) / tan(ray_angle);

// 	y_step = TILE_SIZE;
// 	if (is_ray_facing_up)
// 		y_step *= -1;
// 	x_step = TILE_SIZE / tan(ray_angle);
// 	if ((is_ray_facing_left && x_step > 0) || (is_ray_facing_right && x_step < 0))
// 		x_step *= -1;
// 	float	next_horz_touch_x;
// 	float	next_horz_touch_y;

// 	next_horz_touch_x = x_intercept;
// 	next_horz_touch_y =	y_intercept;
// 	while (next_horz_touch_x >= 0 && next_horz_touch_x <= g_cubfile_data.window_width && next_horz_touch_y >= 0 && next_horz_touch_y <= g_cubfile_data.window_height)
// 	{
// 		float	x_to_check;
// 		float	y_to_check;

// 		x_to_check = next_horz_touch_x;
// 		y_to_check = next_horz_touch_y;
// 		if (is_ray_facing_up)
// 			y_to_check--;
// 		if (map_has_wall_at(x_to_check, y_to_check))
// 		{
// 			horz_wall_hit_x = next_horz_touch_x;
// 			horz_wall_hit_y = next_horz_touch_y;
// 			horz_wall_content = g_map[(int)floor(y_to_check / TILE_SIZE)][(int)floor(x_to_check / TILE_SIZE)];
// 			found_horz_wall_hit = true;
// 			break;
// 		}
// 		next_horz_touch_x += x_step;
// 		next_horz_touch_y += y_step;
// 	}

// 	///////////////////
// 	// VERTICAL PART //
// 	///////////////////
// 	bool	found_vert_wall_hit = false;
// 	float	vert_wall_hit_x;
// 	float	vert_wall_hit_y;
// 	vert_wall_hit_x = 0;
// 	vert_wall_hit_y = 0;
// 	char	vert_wall_content;
// 	// 関数切り分けにするなら必要かも
// 	// float	x_to_check;
// 	// float	y_to_check;

// 	x_intercept = floor(g_player.x / TILE_SIZE) * TILE_SIZE;
// 	if (is_ray_facing_right)
// 		x_intercept += TILE_SIZE;
// 	y_intercept = g_player.y + (x_intercept - g_player.x) * tan(ray_angle);

// 	x_step = TILE_SIZE;
// 	if (is_ray_facing_left)
// 		x_step *= -1;
// 	y_step = TILE_SIZE * tan(ray_angle);
// 	if ((is_ray_facing_down && y_step < 0) || (is_ray_facing_up && y_step > 0))
// 		y_step *= -1;
// 	float	next_vert_touch_x;
// 	float	next_vert_touch_y;

// 	next_vert_touch_x = x_intercept;
// 	next_vert_touch_y =	y_intercept;
// 	while (next_vert_touch_x >= 0 && next_vert_touch_x <= g_cubfile_data.window_width && next_vert_touch_y >= 0 && next_vert_touch_y <= g_cubfile_data.window_height)
// 	{
// 		float	x_to_check;
// 		float	y_to_check;

// 		x_to_check = next_vert_touch_x;
// 		y_to_check = next_vert_touch_y;
// 		if (is_ray_facing_left)
// 			x_to_check--;
// 		if (map_has_wall_at(x_to_check, y_to_check))
// 		{
// 			vert_wall_hit_x = next_vert_touch_x;
// 			vert_wall_hit_y = next_vert_touch_y;
// 			vert_wall_content = g_map[(int)floor(y_to_check / TILE_SIZE)][(int)floor(x_to_check / TILE_SIZE)];
// 			found_vert_wall_hit = true;
// 			break;
// 		}
// 		next_vert_touch_x += x_step;
// 		next_vert_touch_y += y_step;
// 	}
// 	float horz_hit_distance;

// 	if (found_horz_wall_hit)
// 		horz_hit_distance = distance_between_points(g_player.x, g_player.y, horz_wall_hit_x, horz_wall_hit_y);
// 	else
// 		horz_hit_distance = FLT_MAX;
// 	float	vert_hit_distance;

// 	if (found_vert_wall_hit)
// 		vert_hit_distance = distance_between_points(g_player.x, g_player.y, vert_wall_hit_x, vert_wall_hit_y);
// 	else
// 		vert_hit_distance = FLT_MAX;
// 	if (vert_hit_distance < horz_hit_distance)
// 	{
// 		rays[strip_id].distance = vert_hit_distance;
// 		rays[strip_id].wall_hit_x = vert_wall_hit_x;
// 		rays[strip_id].wall_hit_y = vert_wall_hit_y;
// 		rays[strip_id].wall_hit_content = vert_wall_content;
// 		rays[strip_id].was_hit_vertical = true;
// 	}
// 	else
// 	{
// 		rays[strip_id].distance = horz_hit_distance;
// 		rays[strip_id].wall_hit_x = horz_wall_hit_x;
// 		rays[strip_id].wall_hit_y = horz_wall_hit_y;
// 		rays[strip_id].wall_hit_content = horz_wall_content;
// 		rays[strip_id].was_hit_vertical = false;
// 	}
// 	// これ、要る？？
// 	rays[strip_id].ray_angle = ray_angle;
// }

void	cast_all_rays()
{
	float	ray_angle;
	size_t	strip_id;

	ray_angle = g_player.rotation_angle - (FOV_ANGLE / 2);
	strip_id = 0;
	while (strip_id < NUM_RAYS)
	{
		cast_ray(ray_angle, strip_id);
		ray_angle += FOV_ANGLE / NUM_RAYS;
		strip_id++;
	}
}

void	render_rays(void)
{
	size_t	index;

	index = 0;
	g_color = create_trgb(0, 255, 0, 255);
	while (index < NUM_RAYS)
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