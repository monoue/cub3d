/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_and_sort_sprites_data_bonus.h               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:12:04 by monoue            #+#    #+#             */
/*   Updated: 2020/12/09 16:45:27 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UPDATE_AND_SORT_SPRITES_DATA_H
# define UPDATE_AND_SORT_SPRITES_DATA_H

# include <unistd.h>

# include "../defs_bonus.h"
# include "../global/init_g_player_bonus.h"
# include "../global/init_g_sprites_bonus.h"
# include "../global/init_g_distance_proj_plane_bonus.h"
# include "../global/init_g_config_bonus.h"
# include "../utils/normalize_angle_bonus.h"
# include "update_sprite_data_utils_bonus.h"

void	update_and_sort_sprites_data(void);
void	sort_sprites(void);

#endif
