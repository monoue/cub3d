/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_ray_basis_bonus.h                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:11:34 by monoue            #+#    #+#             */
/*   Updated: 2020/12/10 07:19:11 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_WALL_RAY_BASIS_BONUS_H
# define RENDER_WALL_RAY_BASIS_BONUS_H

# include "../../defs_bonus.h"
# include "../../global/init_g_config_bonus.h"
# include "../../global/init_g_color_bonus.h"
# include "../../global/init_g_rays_bonus.h"
# include "../../global/init_g_textures_bonus.h"
# include "../ray/coord_bonus.h"
# include "set_texture_color_bonus.h"
# include "draw_pixel_bonus.h"

void			render_wall_ray_basis(int window_x, int *window_y,
											const int projected_wall_height);

#endif
