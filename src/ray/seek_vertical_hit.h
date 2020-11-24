/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_vertical_hit.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 14:29:17 by monoue            #+#    #+#             */
/*   Updated: 2020/11/24 15:14:22 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEEK_VERTICAL_HIT_H
# define SEEK_VERTICAL_HIT_H

# include "defs.h"
# include "is_ray_facing.h"
# include "player.h"
# include "seek_hit_utils.h"
# include "ray_def.h"

void		seek_vertical_hit(t_ray_materials *vert_hitter, float ray_angle);

#endif
