/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:11:02 by monoue            #+#    #+#             */
/*   Updated: 2020/11/27 15:48:08 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVE_PLAYER_H
# define MOVE_PLAYER_H

# include "../defs.h"
# include "../global/init_g_player.h"
# include "map_has_target_at.h"
# include "../utils/normalize_angle.h"

void			move_player(void);

#endif
