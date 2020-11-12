/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:12:21 by monoue            #+#    #+#             */
/*   Updated: 2020/11/12 16:38:27 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

// t_ray_to_wall	rays[g_cubfile_data.window_width];
// t_ray_to_wall	rays[NUM_RAYS];
t_ray_to_wall	g_rays[MAX_WINDOW_WIDTH];

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
float	get_hit_distance(t_coord *wall_hit_coord, bool is_hit_found)
{
	float	hit_distance;

	if (is_hit_found == true)
		hit_distance = distance_between_points(g_player.x, g_player.y, wall_hit_coord->x, wall_hit_coord->y);
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

char	get_map_at(t_coord *coord)
{
	const int x = (int)(coord->x / TILE_SIZE);
	const int y = (int)(coord->y / TILE_SIZE);

	return (g_map[y][x]);
}

// 構造体作るしかなさそう（intercept_coord, step, wall_hit_coord）
// t_ray_materials	cast_ray_horizontal(t_ray_materials *horz, float ray_angle)
void	cast_ray_horizontal(t_ray_materials *horz, float ray_angle)
{
	horz->is_wall_hit_found = false;
	coord_assign(horz->wall_hit_coord, 0, 0);
	horz->intercept_coord->y = floor(g_player.y / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_down(ray_angle))
		horz->intercept_coord->y += TILE_SIZE;
	horz->intercept_coord->x = g_player.x + (horz->intercept_coord->y - g_player.y) / tan(ray_angle);
	horz->step_coord->y = is_ray_facing_down(ray_angle) ? TILE_SIZE : -(TILE_SIZE);
	horz->step_coord->x = init_parallel_step(ray_angle, HORIZONTAL);
	coord_copy(horz->next_touch_coord, horz->intercept_coord);
	while (is_inside_map(horz->next_touch_coord) == true)
	{
		coord_copy(horz->to_check_coord, horz->next_touch_coord);
		if (is_ray_facing_up(ray_angle))
			horz->to_check_coord->y--;
		if (map_has_wall_at(horz->to_check_coord->x, horz->to_check_coord->y) == true)
		{
			coord_copy(horz->wall_hit_coord, horz->next_touch_coord);
			// horz->wall_content = get_map_at(horz->to_check_coord);
			horz->is_wall_hit_found = true;
			break;
		}
		coord_add(horz->next_touch_coord, horz->step_coord);
	}
	horz->hit_distance = get_hit_distance(horz->wall_hit_coord, horz->is_wall_hit_found);
}



void	cast_ray_vertical(t_ray_materials *vert, float ray_angle)
{
	vert->is_wall_hit_found = false;
	coord_assign(vert->wall_hit_coord, 0, 0);
	vert->intercept_coord->x = floor(g_player.x / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_right(ray_angle))
		vert->intercept_coord->x += TILE_SIZE;
	vert->intercept_coord->y = g_player.y + (vert->intercept_coord->x - g_player.x) * tan(ray_angle);
	vert->step_coord->x = is_ray_facing_right(ray_angle) ? TILE_SIZE : -(TILE_SIZE);
	vert->step_coord->y = init_parallel_step(ray_angle, VERTICAL);
	coord_copy(vert->next_touch_coord, vert->intercept_coord);
	while (is_inside_map(vert->next_touch_coord) == true)
	{
		coord_copy(vert->to_check_coord, vert->next_touch_coord);
		if (is_ray_facing_left(ray_angle))
			vert->to_check_coord->x--;
		if (map_has_wall_at(vert->to_check_coord->x, vert->to_check_coord->y) == true)
		{
			coord_copy(vert->wall_hit_coord, vert->next_touch_coord);
			// vert->wall_content = get_map_at(vert->to_check_coord);
			vert->is_wall_hit_found = true;
			break;
		}
		coord_add(vert->next_touch_coord, vert->step_coord);
	}
	vert->hit_distance = get_hit_distance(vert->wall_hit_coord, vert->is_wall_hit_found);
}

t_ray_materials	*malloc_t_ray_materials()
{
	t_ray_materials	*ray_materials;
	
	ray_materials = malloc(sizeof(t_ray_materials));
	ray_materials->intercept_coord = malloc(sizeof(t_coord));
	ray_materials->step_coord = malloc(sizeof(t_coord));
	ray_materials->wall_hit_coord = malloc(sizeof(t_coord));
	ray_materials->next_touch_coord = malloc(sizeof(t_coord));
	ray_materials->to_check_coord = malloc(sizeof(t_coord));
	return (ray_materials);
}

// void	malloc_two_ray_materials(t_ray_materials *strct1, t_ray_materials *strct2)
// {
// 	strct1 = malloc_t_ray_materials();
// 	strct2 = malloc_t_ray_materials();
// }

void	free_each_t_ray_materials(t_ray_materials *ray_materials)
{
	free(ray_materials->intercept_coord);
	free(ray_materials->step_coord);
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

void	cast_ray_to_sprite(float ray_angle, size_t strip_id)
{
	t_ray_materials	*horz;
	t_ray_materials	*vert;

	horz = malloc_t_ray_materials();
	vert = malloc_t_ray_materials();
	cast_ray_horizontal(horz, ray_angle);
	cast_ray_vertical(vert, ray_angle);
	// TODO: wall_hit_coord, 最後に free
	g_rays[strip_id].wall_hit_coord = malloc(sizeof(t_coord));
	if (vert->hit_distance < horz->hit_distance)
	{
		g_rays[strip_id].distance = vert->hit_distance;
		coord_copy(g_rays[strip_id].wall_hit_coord, vert->wall_hit_coord);
		// g_rays[strip_id].wall_hit_content = vert->wall_content;
		g_rays[strip_id].was_hit_vertical = true;
	}
	else
	{
		g_rays[strip_id].distance = horz->hit_distance;
		coord_copy(g_rays[strip_id].wall_hit_coord, horz->wall_hit_coord);
		// g_rays[strip_id].wall_hit_content = horz->wall_content;
		g_rays[strip_id].was_hit_vertical = false;
	}
	set_ray_direction(&g_rays[strip_id].direction, g_rays[strip_id].was_hit_vertical, is_ray_facing_right(ray_angle), is_ray_facing_down(ray_angle));
	g_rays[strip_id].ray_angle = ray_angle;
	free_t_ray_materials(horz, vert);
	// DI(rays[strip_id].direction);
}


void	cast_ray_to_wall(float ray_angle, size_t strip_id)
{
	t_ray_materials	*horz;
	t_ray_materials	*vert;

	horz = malloc_t_ray_materials();
	vert = malloc_t_ray_materials();
	cast_ray_horizontal(horz, ray_angle);
	cast_ray_vertical(vert, ray_angle);
	// TODO: wall_hit_coord, 最後に free
	g_rays[strip_id].wall_hit_coord = malloc(sizeof(t_coord));
	if (vert->hit_distance < horz->hit_distance)
	{
		g_rays[strip_id].distance = vert->hit_distance;
		coord_copy(g_rays[strip_id].wall_hit_coord, vert->wall_hit_coord);
		// g_rays[strip_id].wall_hit_content = vert->wall_content;
		g_rays[strip_id].was_hit_vertical = true;
	}
	else
	{
		g_rays[strip_id].distance = horz->hit_distance;
		coord_copy(g_rays[strip_id].wall_hit_coord, horz->wall_hit_coord);
		// g_rays[strip_id].wall_hit_content = horz->wall_content;
		g_rays[strip_id].was_hit_vertical = false;
	}
	set_ray_direction(&g_rays[strip_id].direction, g_rays[strip_id].was_hit_vertical, is_ray_facing_right(ray_angle), is_ray_facing_down(ray_angle));
	g_rays[strip_id].ray_angle = ray_angle;
	free_t_ray_materials(horz, vert);
	// DI(rays[strip_id].direction);
}

static void	cast_all_rays(void (*func)(float, size_t))
{
	float	ray_angle;
	size_t	strip_id;

	ray_angle = g_player.rotation_angle - (FOV_ANGLE / 2);
	strip_id = 0;
	while (strip_id < (size_t)g_cubfile_data.window_width)
	{
		normalize_angle(&ray_angle);
		func(ray_angle, strip_id);
		// cast_ray_to_wall(ray_angle, strip_id);
		ray_angle += FOV_ANGLE / g_cubfile_data.window_width;
		strip_id++;
	}
}

void	cast_all_rays_to_wall(void)
{
	cast_all_rays(cast_ray_to_wall);// 関数ポインタ);
}

void	cast_all_rays_to_sprite(void)
{
	cast_all_rays(cast_ray_to_sprite);
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
			g_rays[index].wall_hit_coord->x * MINIMAP_SCALE_FACTOR,
			g_rays[index].wall_hit_coord->y * MINIMAP_SCALE_FACTOR
		);
		index++;
	}
	// test_ray_data(0);
	// test_ray_data(NUM_RAYS - 1);
}