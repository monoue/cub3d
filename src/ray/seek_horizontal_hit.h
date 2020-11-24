/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_horizontal_hit.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 14:24:15 by monoue            #+#    #+#             */
/*   Updated: 2020/11/24 15:14:29 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEEK_HORIZONTAL_HIT_H
# define SEEK_HORIZONTAL_HIT_H

# include "defs.h"
# include "is_ray_facing.h"
# include "player.h"
# include "seek_hit_utils.h"
# include "ray_def.h"

void	seek_horizontal_hit(t_ray_materials *horz_hitter, float ray_angle);

#endif
