/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:10:44 by monoue            #+#    #+#             */
/*   Updated: 2020/11/26 17:17:30 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_LOOP_H
# define GAME_LOOP_H

# include "../../minilibx/mlx.h"

# include "event_hook.h"
# include "move_player.h"
# include "update_and_sort_sprites_data.h"

# include "ray/cast_all_rays_to_wall.h"

# include "render/render_background.h"
# include "render/render_mini_map.h"
# include "render/render_wall_ray_basis.h"
# include "render/render_sprites.h"

# include "../utils/create_trgb.h"

# include "../global/init_g_img.h"
# include "../global/init_g_save_flag.h"

# include "../save_image/save_image.h"

int	game_loop(void *null);

#endif
