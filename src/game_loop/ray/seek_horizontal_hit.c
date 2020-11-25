/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_horizontal_hit.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 14:23:47 by monoue            #+#    #+#             */
/*   Updated: 2020/11/24 15:32:20 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "seek_horizontal_hit.h"

static void	init_horz_hitter_step(t_coord *step, float ray_angle)
{
	step->y = is_ray_facing_down(ray_angle) ? TILE_SIZE : -(TILE_SIZE);
	step->x = TILE_SIZE / tan(ray_angle);
	if ((is_ray_facing_left(ray_angle) && step->x > 0)
							|| (is_ray_facing_right(ray_angle) && step->x < 0))
		step->x *= -1;
}

static void	init_horz_hitter_intercept(t_coord *intercept, float ray_angle)
{
	intercept->y = floor(g_player.y / TILE_SIZE) * TILE_SIZE;
	if (is_ray_facing_down(ray_angle))
		intercept->y += TILE_SIZE;
	intercept->x = g_player.x + (intercept->y - g_player.y) / tan(ray_angle);
}

void		seek_horizontal_hit(t_ray_materials *horz_hitter, float ray_angle)
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
		if (map_has_wall_at(horz_hitter->to_check_coord->x,
										horz_hitter->to_check_coord->y) == true)
		{
			coord_copy(horz_hitter->wall_hit_coord,
												horz_hitter->next_touch_coord);
			horz_hitter->is_wall_hit_found = true;
			break ;
		}
		coord_add(horz_hitter->next_touch_coord, horz_hitter->step);
	}
	horz_hitter->hit_distance = get_hit_distance(horz_hitter->wall_hit_coord,
												horz_hitter->is_wall_hit_found);
}
