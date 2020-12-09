/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_horizontal_hit_bonus.h                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 14:24:15 by monoue            #+#    #+#             */
/*   Updated: 2020/12/09 16:45:36 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEEK_HORIZONTAL_HIT_H
# define SEEK_HORIZONTAL_HIT_H

# include "../../defs_bonus.h"
# include "../../global/init_g_player_bonus.h"
# include "is_ray_facing_bonus.h"
# include "seek_hit_utils_bonus.h"
# include "../map_has_target_at_bonus.h"
# include "ray_def_bonus.h"

void	seek_horizontal_hit(t_ray_materials *horz_hitter, float ray_angle);

#endif
