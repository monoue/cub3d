/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_all_rays_to_wall_bonus.h                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:11:16 by monoue            #+#    #+#             */
/*   Updated: 2020/12/09 16:45:36 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAST_ALL_RAYS_TO_WALL_H
# define CAST_ALL_RAYS_TO_WALL_H

# include "cast_ray_to_wall_utils_bonus.h"
# include "../../defs_bonus.h"
# include "../../global/init_g_player_bonus.h"
# include "../../utils/normalize_angle_bonus.h"
# include "../../global/init_g_player_bonus.h"
# include "seek_horizontal_hit_bonus.h"
# include "seek_vertical_hit_bonus.h"
# include "../../set_config/set_config_bonus.h"

void	cast_all_rays_to_wall(void);

#endif
