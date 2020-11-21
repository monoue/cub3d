/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:12:23 by monoue            #+#    #+#             */
/*   Updated: 2020/11/21 13:12:39 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WALL_H
# define WALL_H

# include "defs.h"
# include "graphics.h" // g_color
# include "texture.h"
# include "render_wall_ray_basis.h"

extern float	g_distance_proj_plane;

// void	set_texture_color(t_texture texture, int x, int y);
void	render_background(void);
int		calc_projected_object_height(float angle_to_object, float distance_to_object);
#endif
