/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sprites_data.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:12:04 by monoue            #+#    #+#             */
/*   Updated: 2020/11/26 13:46:52 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UPDATE_SPRITES_DATA_H
# define UPDATE_SPRITES_DATA_H

# include <unistd.h>

# include "../defs.h"
# include "../global/init_g_player.h"
# include "../global/init_g_sprites.h"
# include "../global/init_g_distance_proj_plane.h"
# include "../global/init_g_cubfile_data.h"
# include "../utils/normalize_angle.h"

void			update_and_sort_sprites_data(void);

#endif
