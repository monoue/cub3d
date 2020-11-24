/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_all_rays_to_wall.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:11:16 by monoue            #+#    #+#             */
/*   Updated: 2020/11/24 16:26:06 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAST_ALL_RAYS_TO_WALL_H
# define CAST_ALL_RAYS_TO_WALL_H

# include "cast_ray_to_wall_utils.h"
# include "defs.h"
# include "normalize_angle.h"
# include "player.h"
# include "seek_horizontal_hit.h"
# include "seek_vertical_hit.h"
# include "set_cubfile_data.h"

void	cast_all_rays_to_wall(void);

#endif
