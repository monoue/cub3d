/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_has_wall_at.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:10:50 by monoue            #+#    #+#             */
/*   Updated: 2020/11/25 11:58:56 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HAS_WALL_AT_H
# define MAP_HAS_WALL_AT_H

// # include "create_maps.h"
# include "../defs.h"
# include "../global/init_g_map.h"
// # include "init_mlx.h"
// # include "../map_error.h"

bool	map_has_wall_at(float x, float y);
bool	is_space_at(const float pixel_x, const float pixel_y);

#endif
