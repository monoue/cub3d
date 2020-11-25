/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:10:44 by monoue            #+#    #+#             */
/*   Updated: 2020/11/25 13:08:57 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_LOOP_H
# define GAME_LOOP_H

# include "event_hook.h"
# include "move_player.h"
# include "ray/cast_all_rays_to_wall.h"
# include "render/render_background.h"
# include "render/render_mini_map.h"
# include "render/render_wall_ray_basis.h"
# include "render/render_sprites.h"
# include "update_sprites_data.h"
# include "../../minilibx/mlx.h"
# include "../utils/create_trgb.h"
# include "../global/init_g_img.h"

int	game_loop(void *null);

#endif
