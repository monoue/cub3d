/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_vertical_hit_bonus.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 14:29:17 by monoue            #+#    #+#             */
/*   Updated: 2020/12/10 07:19:11 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEEK_VERTICAL_HIT_BONUS_H
# define SEEK_VERTICAL_HIT_BONUS_H

# include "../../defs_bonus.h"
# include "../../global/init_g_player_bonus.h"
# include "is_ray_facing_bonus.h"
# include "seek_hit_utils_bonus.h"
# include "../map_has_target_at_bonus.h"
# include "ray_def_bonus.h"

void		seek_vertical_hit(t_ray_materials *vert_hitter, float ray_angle);

#endif
