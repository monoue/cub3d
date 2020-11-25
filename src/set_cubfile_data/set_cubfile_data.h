/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   src/set_cubfile_data/set_cubfile_data.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:11:56 by monoue            #+#    #+#             */
/*   Updated: 2020/11/25 09:18:09 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_CUBFILE_DATA_H
# define SET_CUBFILE_DATA_H

# include <fcntl.h>

# include "create_maps.h"
# include "src/libft/libft.h"
# include "src/defs.h"
# include "src/global/init_g_ids.h"
# include "src/set_cubfile_data/create_maps.h"
# include "src/set_cubfile_data/get_line_data_utils.h"
# include "src/set_cubfile_data/is_map_line.h"
# include "src/set_cubfile_data/set_color.h"
# include "src/set_cubfile_data/set_player_spawning_data.h"
# include "src/set_cubfile_data/set_sprite_position.h"

void	set_cubfile_data(char *filename);

#endif
