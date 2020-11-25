/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:11:28 by monoue            #+#    #+#             */
/*   Updated: 2020/11/25 12:26:43 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_SPRITES_H
# define RENDER_SPRITES_H

# include "../../defs.h"
# include "../../global/init_g_color.h"
# include "../../global/init_g_cubfile_data.h"
# include "../../global/init_g_distance_proj_plane.h"
# include "../../global/init_g_player.h"
# include "../../global/init_g_rays.h"
# include "../../global/init_g_sprites.h"
# include "../../global/init_g_textures.h"
# include "../../utils/create_trgb.h"
# include "../../utils/normalize_angle.h"
# include "../ray/coord.h"
# include "draw_pixel.h"
# include "set_texture_color.h"

void	render_sprites(void);

#endif
