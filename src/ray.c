/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:12:21 by monoue            #+#    #+#             */
/*   Updated: 2020/11/20 20:13:39 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_ray_to_wall	g_rays[MAX_WINDOW_WIDTH];

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

bool	is_inside_map(t_coord *coord)
{
	const float		x = coord->x;
	const float		y = coord->y;
	const size_t	edge = MAX_MAP_LEN * TILE_SIZE;

    return (x >= 0 && x <= edge && y >= 0 && y <= edge);
}

static void	set_ray_direction(t_textures_num *direction, bool was_hit_vertical, bool is_ray_facing_right, bool is_ray_facing_down)
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

float	get_hit_distance(t_coord *wall_hit_coord, bool is_hit_found)
{
	float	hit_distance;

	if (is_hit_found == true)
		hit_distance = distance_between_points(g_player.x, g_player.y, wall_hit_coord->x, wall_hit_coord->y);
	else
		hit_distance = FLT_MAX;
	return (hit_distance);
}

void	init_horz_hitter_step(t_coord *step, float ray_angle)
{
	step->y = is_ray_facing_down(ray_angle) ? TILE_SIZE : -(TILE_SIZE);
	step->x = TILE_SIZE / tan(ray_angle);
	if ((is_ray_facing_left(ray_angle) && step->x > 0) || (is_ray_facing_right(ray_angle) && step->x < 0))
		step->x *= -1;
}

void	init_horz_hitter_intercept(t_coord *intercept, float ray_angle)
{
	intercept->y = floor(g_player.y / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_down(ray_angle))
		intercept->y += TILE_SIZE;
	intercept->x = g_player.x + (intercept->y - g_player.y) / tan(ray_angle);
}

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
			horz_hitter->is_wall_hit_found = true;
			break;
		}
		coord_add(horz_hitter->next_touch_coord, horz_hitter->step);
	}
	horz_hitter->hit_distance = get_hit_distance(horz_hitter->wall_hit_coord, horz_hitter->is_wall_hit_found);
}

void	init_vert_hitter_step(t_coord *step, float ray_angle)
{
	step->x = is_ray_facing_right(ray_angle) ? TILE_SIZE : -(TILE_SIZE);
	step->y = TILE_SIZE * tan(ray_angle);
	if ((is_ray_facing_down(ray_angle) && step->y < 0) || (is_ray_facing_up(ray_angle) && step->y > 0))
		step->y *= -1;
}

void	init_vert_hitter_intercept(t_coord *intercept, float ray_angle)
{
	intercept->x = floor(g_player.x / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_right(ray_angle))
		intercept->x += TILE_SIZE;
	intercept->y = g_player.y + (intercept->x - g_player.x) * tan(ray_angle);
}

void	seek_vertical_hit(t_ray_materials *vert_hitter, float ray_angle)
{
	vert_hitter->is_wall_hit_found = false;
	coord_assign(vert_hitter->wall_hit_coord, 0, 0);
	init_vert_hitter_intercept(vert_hitter->intercept, ray_angle);
	init_vert_hitter_step(vert_hitter->step, ray_angle);
	coord_copy(vert_hitter->next_touch_coord, vert_hitter->intercept);
	while (is_inside_map(vert_hitter->next_touch_coord) == true)
	{
		coord_copy(vert_hitter->to_check_coord, vert_hitter->next_touch_coord);
		if (is_ray_facing_left(ray_angle))
			vert_hitter->to_check_coord->x--;
		if (map_has_wall_at(vert_hitter->to_check_coord->x, vert_hitter->to_check_coord->y) == true)
		{
			coord_copy(vert_hitter->wall_hit_coord, vert_hitter->next_touch_coord);
			vert_hitter->is_wall_hit_found = true;
			break;
		}
		coord_add(vert_hitter->next_touch_coord, vert_hitter->step);
	}
	vert_hitter->hit_distance = get_hit_distance(vert_hitter->wall_hit_coord, vert_hitter->is_wall_hit_found);
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

void	cast_ray_to_wall(float ray_angle, size_t strip_id)
{
	t_ray_materials	*horz_hitter;
	t_ray_materials	*vert_hitter;

	horz_hitter = malloc_t_ray_materials();
	vert_hitter = malloc_t_ray_materials();
	seek_horizontal_hit(horz_hitter, ray_angle);
	seek_vertical_hit(vert_hitter, ray_angle);
	// TODO: wall_hit_coord, 最後に free
	g_rays[strip_id].wall_hit_coord = malloc(sizeof(t_coord));
	if (vert_hitter->hit_distance < horz_hitter->hit_distance)
	{
		g_rays[strip_id].distance_to_wall = vert_hitter->hit_distance;
		coord_copy(g_rays[strip_id].wall_hit_coord, vert_hitter->wall_hit_coord);
		g_rays[strip_id].was_hit_vertical = true;
	}
	else
	{
		g_rays[strip_id].distance_to_wall = horz_hitter->hit_distance;
		coord_copy(g_rays[strip_id].wall_hit_coord, horz_hitter->wall_hit_coord);
		g_rays[strip_id].was_hit_vertical = false;
	}
	set_ray_direction(&g_rays[strip_id].wall_hit_direction, g_rays[strip_id].was_hit_vertical, is_ray_facing_right(ray_angle), is_ray_facing_down(ray_angle));
	g_rays[strip_id].ray_angle = ray_angle;
	free_t_ray_materials(horz_hitter, vert_hitter);
}

static void	cast_all_ray_to_wall(void)
{
	float	ray_angle;
	size_t	strip_id;

	ray_angle = g_player.rotation_angle - (FOV_ANGLE / 2);
	strip_id = 0;
	while (strip_id < (size_t)g_cubfile_data.window_width)
	{
		normalize_angle(&ray_angle);
		cast_ray_to_wall(ray_angle, strip_id);
		ray_angle += FOV_ANGLE / g_cubfile_data.window_width;
		strip_id++;
	}
}

void	cast_all_rays_to_wall(void)
{
	cast_all_ray_to_wall();
}