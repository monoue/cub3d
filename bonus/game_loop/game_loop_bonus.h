/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:10:44 by monoue            #+#    #+#             */
/*   Updated: 2020/12/10 07:19:11 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_LOOP_BONUS_H
# define GAME_LOOP_BONUS_H

# include "../../minilibx/mlx.h"

# include "event_hook_bonus.h"
# include "move_player_bonus.h"
# include "update_and_sort_sprites_data_bonus.h"

# include "ray/cast_all_rays_to_wall_bonus.h"

# include "render/render_background_bonus.h"
# include "render/render_mini_map_bonus.h"
# include "render/render_wall_ray_basis_bonus.h"
# include "render/render_sprites_bonus.h"

# include "../utils/create_trgb_bonus.h"

# include "../global/init_g_img_bonus.h"
# include "../global/init_g_minimap_flag_bonus.h"
# include "../global/init_g_save_flag_bonus.h"

# include "../save_image/save_image_bonus.h"

int	game_loop(void *null);

#endif
