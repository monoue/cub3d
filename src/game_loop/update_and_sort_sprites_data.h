/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_and_sort_sprites_data.h                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:12:04 by monoue            #+#    #+#             */
/*   Updated: 2020/11/30 12:37:51 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UPDATE_AND_SORT_SPRITES_DATA_H
# define UPDATE_AND_SORT_SPRITES_DATA_H

# include <unistd.h>

# include "../defs.h"
# include "../global/init_g_player.h"
# include "../global/init_g_sprites.h"
# include "../global/init_g_distance_proj_plane.h"
# include "../global/init_g_config.h"
# include "../utils/normalize_angle.h"
# include "update_sprite_data_utils.h"

void			update_and_sort_sprites_data(void);

#endif
