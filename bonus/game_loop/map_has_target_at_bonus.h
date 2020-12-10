/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_has_target_at_bonus.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:10:50 by monoue            #+#    #+#             */
/*   Updated: 2020/12/10 07:19:11 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HAS_TARGET_AT_BONUS_H
# define MAP_HAS_TARGET_AT_BONUS_H

# include "../defs_bonus.h"
# include "../global/init_g_map_bonus.h"

bool	map_has_wall_at(float x, float y);
bool	map_has_collision_objection_at(float x, float y);

#endif
