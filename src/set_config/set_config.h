/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_config.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 13:06:31 by monoue            #+#    #+#             */
/*   Updated: 2020/12/11 09:06:03 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_CONFIG_H
# define SET_CONFIG_H

# include <fcntl.h>

# include "create_maps.h"
# include "free_str_array.h"
# include "../../libft/libft.h"
# include "../defs.h"
# include "exit_if_map_is_not_surrounded_by_walls.h"
# include "create_maps.h"
# include "get_line_data_utils.h"
# include "is_map_line.h"
# include "set_color.h"
# include "set_player_spawning_data.h"
# include "set_sprite_position.h"
# include "set_texture_if_valid.h"

void	set_config(char *filename);

#endif
