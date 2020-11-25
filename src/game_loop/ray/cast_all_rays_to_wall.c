/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_all_rays_to_wall.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 14:12:21 by monoue            #+#    #+#             */
/*   Updated: 2020/11/24 16:20:53 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cast_all_rays_to_wall.h"

static void	cast_ray_to_wall(float ray_angle, size_t strip_id)
{
	t_ray_materials	*horz_hitter;
	t_ray_materials	*vert_hitter;

	horz_hitter = malloc_t_ray_materials();
	vert_hitter = malloc_t_ray_materials();
	seek_horizontal_hit(horz_hitter, ray_angle);
	seek_vertical_hit(vert_hitter, ray_angle);
	set_ray_hit_data(horz_hitter, vert_hitter, ray_angle, strip_id);
	free_t_ray_materials(horz_hitter, vert_hitter);
}

void		cast_all_rays_to_wall(void)
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
