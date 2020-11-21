/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:10:50 by monoue            #+#    #+#             */
/*   Updated: 2020/11/21 16:44:20 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_CHECK_H
# define MAP_CHECK_H

# include "create_maps.h"
# include "defs.h"
# include "init_mlx.h"
# include "map_error.h"

bool	map_has_target_at(float x, float y, char c);
bool	map_has_sprite_at(float x, float y);
bool	map_has_wall_at(float x, float y);
bool	is_space_at(const float pixel_x, const float pixel_y);
bool	is_out_of_window(float x, float y);

#endif
