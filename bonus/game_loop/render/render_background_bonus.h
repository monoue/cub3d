/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_background_bonus.h                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:12:23 by monoue            #+#    #+#             */
/*   Updated: 2020/12/10 07:19:11 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_BACKGROUND_BONUS_H
# define RENDER_BACKGROUND_BONUS_H

# include "../../defs_bonus.h"
# include "../../global/init_g_player_bonus.h"
# include "../../global/init_g_color_bonus.h"
# include "../../global/init_g_distance_proj_plane_bonus.h"
# include "../../global/init_g_rays_bonus.h"
# include "render_wall_ray_basis_bonus.h"
# include "draw_pixel_bonus.h"

void	render_background(void);
int		calc_projected_object_height(float angle_to_object,
													float distance_to_object);

#endif
