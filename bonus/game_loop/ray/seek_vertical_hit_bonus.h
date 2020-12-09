/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_vertical_hit.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 14:29:17 by monoue            #+#    #+#             */
/*   Updated: 2020/11/27 15:48:08 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEEK_VERTICAL_HIT_H
# define SEEK_VERTICAL_HIT_H

# include "../../defs.h"
# include "../../global/init_g_player.h"
# include "is_ray_facing.h"
# include "seek_hit_utils.h"
# include "../map_has_target_at.h"
# include "ray_def.h"

void		seek_vertical_hit(t_ray_materials *vert_hitter, float ray_angle);

#endif
