/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_g_rays.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 12:06:20 by monoue            #+#    #+#             */
/*   Updated: 2020/11/25 12:09:45 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_G_RAYS_H
# define INIT_G_RAYS_H

# include "../defs.h"
# include "../game_loop/ray/coord.h"

typedef struct	s_ray_to_wall {
	float			ray_angle;
	t_coord			*wall_hit_coord;
	float			distance_to_wall;
	bool			was_hit_vertical;
	t_textures_num	wall_hit_direction;
}				t_ray_to_wall;

extern t_ray_to_wall	g_rays[MAX_WINDOW_WIDTH];

#endif
