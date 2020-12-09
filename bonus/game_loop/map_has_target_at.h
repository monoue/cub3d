/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_has_wall_at.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:10:50 by monoue            #+#    #+#             */
/*   Updated: 2020/11/27 15:42:49 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HAS_TARGET_AT_H
# define MAP_HAS_TARGET_AT_H

# include "../defs.h"
# include "../global/init_g_map.h"

bool	map_has_wall_at(float x, float y);
bool	map_has_collision_objection_at(float x, float y);

#endif
