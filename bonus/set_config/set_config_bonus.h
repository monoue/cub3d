/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_config_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 13:06:31 by monoue            #+#    #+#             */
/*   Updated: 2020/12/09 16:46:15 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_CONFIG_H
# define SET_CONFIG_H

# include <fcntl.h>

# include "create_maps_bonus.h"
# include "free_str_array_bonus.h"
# include "../../libft/libft.h"
# include "../defs_bonus.h"
# include "exit_if_map_is_not_surrounded_by_walls_bonus.h"
# include "../set_config/create_maps_bonus.h"
# include "../set_config/get_line_data_utils_bonus.h"
# include "../set_config/is_map_line_bonus.h"
# include "../set_config/set_color_bonus.h"
# include "../set_config/set_player_spawning_data_bonus.h"
# include "../set_config/set_sprite_position_bonus.h"
# include "../set_config/set_texture_if_valid_bonus.h"

void	set_config(char *filename);

#endif
