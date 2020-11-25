/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:11:02 by monoue            #+#    #+#             */
/*   Updated: 2020/11/25 10:15:10 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVE_PLAYER_H
# define MOVE_PLAYER_H

# include "src/defs.h"
# include "src/global/init_g_player.h"
# include "map_has_wall_at.h"
# include "normalize_angle.h"

void			move_player(void);

#endif
