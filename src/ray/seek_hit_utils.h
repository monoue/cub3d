/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_hit_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 14:15:32 by monoue            #+#    #+#             */
/*   Updated: 2020/11/24 14:38:39 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEEK_HIT_UTILS_H
# define SEEK_HIT_UTILS_H

# include <float.h>
# include <stdbool.h>

# include "coord.h"
# include "defs.h"
# include "player.h"

float	get_hit_distance(t_coord *wall_hit_coord, bool is_hit_found);
bool	is_inside_map(t_coord *coord);

#endif
