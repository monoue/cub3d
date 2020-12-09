/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_vertical_hit_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 14:29:31 by monoue            #+#    #+#             */
/*   Updated: 2020/12/09 16:45:36 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "seek_vertical_hit_bonus.h"

static void	init_vert_hitter_step(t_coord *step, float ray_angle)
{
	step->x = is_ray_facing_right(ray_angle) ? TILE_SIZE : -(TILE_SIZE);
	step->y = TILE_SIZE * tan(ray_angle);
	if ((is_ray_facing_down(ray_angle) && step->y < 0)
		|| (is_ray_facing_up(ray_angle) && step->y > 0))
		step->y *= -1;
}

static void	init_vert_hitter_intercept(t_coord *intercept, float ray_angle)
{
	intercept->x = floor(g_player.x / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_right(ray_angle))
		intercept->x += TILE_SIZE;
	intercept->y = g_player.y + (intercept->x - g_player.x) * tan(ray_angle);
}

void		seek_vertical_hit(t_ray_materials *vert_hitter, float ray_angle)
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
		if (map_has_wall_at(vert_hitter->to_check_coord->x,
										vert_hitter->to_check_coord->y) == true)
		{
			coord_copy(vert_hitter->wall_hit_coord,
												vert_hitter->next_touch_coord);
			vert_hitter->is_wall_hit_found = true;
			break ;
		}
		coord_add(vert_hitter->next_touch_coord, vert_hitter->step);
	}
	vert_hitter->hit_distance = get_hit_distance(vert_hitter->wall_hit_coord,
												vert_hitter->is_wall_hit_found);
}
