/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_wall_ray_basis.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:11:34 by monoue            #+#    #+#             */
/*   Updated: 2020/11/25 09:55:01 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_WALL_RAY_BASIS_H
# define RENDER_WALL_RAY_BASIS_H

# include "src/defs.h"
# include "src/global/init_g_cubfile_data.h"
# include "graphics.h"

void			render_wall_ray_basis(int window_x, int *window_y,
											const int projected_wall_height);
void			set_texture_color(t_texture texture, int x, int y);

#endif
