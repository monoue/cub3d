/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_hit_utils_bonus.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 14:15:32 by monoue            #+#    #+#             */
/*   Updated: 2020/12/09 16:45:36 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEEK_HIT_UTILS_H
# define SEEK_HIT_UTILS_H

# include <float.h>
# include <stdbool.h>

# include "coord_bonus.h"
# include "../../defs_bonus.h"
# include "../../global/init_g_player_bonus.h"

float	get_hit_distance(t_coord *wall_hit_coord, bool is_hit_found);
bool	is_inside_map(t_coord *coord);

#endif
