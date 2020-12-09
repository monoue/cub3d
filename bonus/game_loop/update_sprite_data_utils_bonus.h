/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_sprite_data_utils_bonus.h                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 15:32:03 by monoue            #+#    #+#             */
/*   Updated: 2020/12/09 16:45:27 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UPDATE_SPRITE_DATA_UTILS_H
# define UPDATE_SPRITE_DATA_UTILS_H

# include "../defs_bonus.h"
# include "../global/init_g_distance_proj_plane_bonus.h"
# include "../global/init_g_sprites_bonus.h"
# include "../global/init_g_player_bonus.h"
# include "../global/init_g_config_bonus.h"
# include "../utils/normalize_angle_bonus.h"

void	set_distance_from_player(size_t index);
void	set_angle_diff_from_player(size_t index);
void	set_perp_distance_from_player(size_t index);
void	set_projected_tile_size(size_t index);
void	set_projection_edges(size_t index);

#endif
