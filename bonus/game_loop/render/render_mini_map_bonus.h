/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mini_map_bonus.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:11:23 by monoue            #+#    #+#             */
/*   Updated: 2020/12/10 07:19:11 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_MINI_MAP_BONUS_H
# define RENDER_MINI_MAP_BONUS_H

# include "../../defs_bonus.h"
# include "../../global/init_g_player_bonus.h"
# include "../../global/init_g_rays_bonus.h"
# include "../../global/init_g_map_bonus.h"
# include "../../global/init_g_config_bonus.h"
# include "../../global/init_g_sprites_bonus.h"
# include "../../utils/create_trgb_bonus.h"
# include "draw_shape_bonus.h"

void	render_mini_map(void);
void	render_player(void);
void	render_lines_to_sprites_center(void);

#endif
