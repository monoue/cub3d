/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cubfile_data.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 13:06:31 by monoue            #+#    #+#             */
/*   Updated: 2020/11/25 13:06:39 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_CUBFILE_DATA_H
# define SET_CUBFILE_DATA_H

# include <fcntl.h>

# include "create_maps.h"
# include "../libft/libft.h"
# include "../defs.h"
# include "exit_if_map_is_not_surrounded_by_walls.h"
# include "../global/init_g_ids.h"
# include "../set_cubfile_data/create_maps.h"
# include "../set_cubfile_data/get_line_data_utils.h"
# include "../set_cubfile_data/is_map_line.h"
# include "../set_cubfile_data/set_color.h"
# include "../set_cubfile_data/set_player_spawning_data.h"
# include "../set_cubfile_data/set_sprite_position.h"
# include "../set_cubfile_data/set_texture.h"

void	set_cubfile_data(char *filename);

#endif
