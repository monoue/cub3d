/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mini_map.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:11:23 by monoue            #+#    #+#             */
/*   Updated: 2020/11/25 12:12:30 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_MINI_MAP_H
# define RENDER_MINI_MAP_H

# include "../../defs.h"
# include "../../global/init_g_player.h"
# include "../../global/init_g_rays.h"
# include "../../global/init_g_map.h"
# include "../../global/init_g_cubfile_data.h"
# include "../../global/init_g_sprites.h"
# include "../../utils/create_trgb.h"
# include "draw_shape.h"

void	render_mini_map(void);
void	render_player(void);
void	render_lines_to_sprites_center(void);

#endif
