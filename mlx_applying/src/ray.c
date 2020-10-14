#include "ray.h"

t_ray	rays[NUM_RAYS];

void	normalize_angle(float *angle)
{
	*angle = remainder(*angle, TWO_PI);
	if (*angle < 0)
		*angle += TWO_PI;
}

float	distance_between_points(float x1, float y1, float x2, float y2)
{
	const float	x_diff = x2 - x1;
	const float	y_diff = y2 - y1;

	return (sqrt(pow(x_diff, 2) + pow(y_diff, 2)));
}

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
	float	horzHitDistance = (found_horz_wall_hit)
		? distance_between_points(g_player.x, g_player.y, horz_wall_hit_x, horz_wall_hit_y)
		: FLT_MAX;
	// const float	vert_hit_distance = (found_vert_wall_hit)
	float	vert_hit_distance = (found_vert_wall_hit)
		? distance_between_points(g_player.x, g_player.y, vert_wall_hit_x, vert_wall_hit_y)
		: FLT_MAX;
	if (vert_hit_distance < horzHitDistance)
	{
		rays[stripId].distance = vert_hit_distance;
		rays[stripId].wall_hit_x = vert_wall_hit_x;
		rays[stripId].wall_hit_y = vert_wall_hit_y;
		rays[stripId].wall_hit_content = vert_wall_content;
		rays[stripId].was_hit_vertical = true;
	}
	else
	{
		rays[stripId].distance = horzHitDistance;
		rays[stripId].wall_hit_x = horz_wall_hit_x;
		rays[stripId].wall_hit_y = horz_wall_hit_y;
		rays[stripId].wall_hit_content = horz_wall_content;
		rays[stripId].was_hit_vertical = false;
	}
	rays[stripId].ray_angle = ray_angle;
}

void	cast_all_rays(void)
{
	float		ray_angle;
	int			col;

	col = 0;
	while (col < NUM_RAYS)
	{
		// rotationAngle は、向いている真っ正面。
		// col = 0 の時は開始の角度になるようマイナスになり、半分でど真ん中、そして段々とプラスの端っこへ
		ray_angle = g_player.rotation_angle + atan((col - (NUM_RAYS / 2)) / DIST_PROJ_PLANE);
		cast_ray(ray_angle, col);
		col++;
	}
}


void	render_rays(void)
{
	int	index;

	index = 0;
	while (index < NUM_RAYS)
	{
		draw_line
		(
			g_player.x * MINIMAP_SCALE_FACTOR,
			g_player.y * MINIMAP_SCALE_FACTOR,
			rays[index].wall_hit_x * MINIMAP_SCALE_FACTOR,
			rays[index].wall_hit_y * MINIMAP_SCALE_FACTOR,
			0xFF0000FF
		);
		index++;
	}
}