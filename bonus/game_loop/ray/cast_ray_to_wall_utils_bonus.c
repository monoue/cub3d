/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray_to_wall_utils_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:16:08 by monoue            #+#    #+#             */
/*   Updated: 2020/12/09 16:45:36 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cast_ray_to_wall_utils_bonus.h"

t_ray_materials	*malloc_t_ray_materials(void)
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

void			free_each_t_ray_materials(t_ray_materials *ray_materials)
{
	free(ray_materials->intercept);
	free(ray_materials->step);
	free(ray_materials->wall_hit_coord);
	free(ray_materials->next_touch_coord);
	free(ray_materials->to_check_coord);
	free(ray_materials);
}

void			free_t_ray_materials(t_ray_materials *struct1,
													t_ray_materials *struct2)
{
	free_each_t_ray_materials(struct1);
	free_each_t_ray_materials(struct2);
}

void			set_ray_direction(t_textures_num *direction,
	bool was_hit_vertical, bool is_ray_facing_right, bool is_ray_facing_down)
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

void			set_ray_hit_data(t_ray_materials *horz_hitter,
				t_ray_materials *vert_hitter, float ray_angle, size_t strip_id)
{
	if (vert_hitter->hit_distance < horz_hitter->hit_distance)
	{
		g_rays[strip_id].distance_to_wall = vert_hitter->hit_distance;
		coord_copy(g_rays[strip_id].wall_hit_coord,
											vert_hitter->wall_hit_coord);
		g_rays[strip_id].was_hit_vertical = true;
	}
	else
	{
		g_rays[strip_id].distance_to_wall = horz_hitter->hit_distance;
		coord_copy(g_rays[strip_id].wall_hit_coord,
											horz_hitter->wall_hit_coord);
		g_rays[strip_id].was_hit_vertical = false;
	}
	set_ray_direction(&g_rays[strip_id].wall_hit_direction,
		g_rays[strip_id].was_hit_vertical, is_ray_facing_right(ray_angle),
		is_ray_facing_down(ray_angle));
	g_rays[strip_id].ray_angle = ray_angle;
}
