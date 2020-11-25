/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:10:44 by monoue            #+#    #+#             */
/*   Updated: 2020/11/25 10:43:40 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_LOOP_H
# define GAME_LOOP_H

# include "event_hook.h"
# include "move_player.h"
# include "cast_all_rays_to_wall.h"
# include "render/render_background.h"
# include "render/render_mini_map.h"
# include "render/render_wall_ray_basis.h"
# include "render/render_sprites.h"
# include "set_color.h"
# include "update_sprites_data.h"
# include "../minilibx/mlx.h"

int	game_loop(void *null);

extern	t_mlx g_mlx;
extern	t_img g_img;

#endif
