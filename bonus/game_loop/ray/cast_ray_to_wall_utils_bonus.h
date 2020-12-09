/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray_to_wall_utils_bonus.h                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:15:40 by monoue            #+#    #+#             */
/*   Updated: 2020/12/09 16:45:36 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAST_RAY_TO_WALL_UTILS_H
# define CAST_RAY_TO_WALL_UTILS_H

# include "coord_bonus.h"
# include "../../defs_bonus.h"
# include "../../global/init_g_rays_bonus.h"
# include "ray_def_bonus.h"
# include "is_ray_facing_bonus.h"

t_ray_materials	*malloc_t_ray_materials(void);
void			free_each_t_ray_materials(t_ray_materials *ray_materials);
void			free_t_ray_materials(t_ray_materials *struct1,
													t_ray_materials *struct2);
void			set_ray_direction(t_textures_num *direction,
	bool was_hit_vertical, bool is_ray_facing_right, bool is_ray_facing_down);
void			set_ray_hit_data(t_ray_materials *horz_hitter,
				t_ray_materials *vert_hitter, float ray_angle, size_t strip_id);

#endif
