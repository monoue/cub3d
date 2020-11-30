/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_ray_basis.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:11:34 by monoue            #+#    #+#             */
/*   Updated: 2020/11/30 12:37:51 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_WALL_RAY_BASIS_H
# define RENDER_WALL_RAY_BASIS_H

# include "../../defs.h"
# include "../../global/init_g_config.h"
# include "../../global/init_g_color.h"
# include "../../global/init_g_rays.h"
# include "../../global/init_g_textures.h"
# include "../ray/coord.h"
# include "set_texture_color.h"
# include "draw_pixel.h"

void			render_wall_ray_basis(int window_x, int *window_y,
											const int projected_wall_height);

#endif
