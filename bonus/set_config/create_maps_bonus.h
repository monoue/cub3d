/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_maps_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:10:13 by monoue            #+#    #+#             */
/*   Updated: 2020/12/11 09:07:38 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CREATE_MAPS_BONUS_H
# define CREATE_MAPS_BONUS_H

# include "is_map_line_bonus.h"
# include "../../libft/libft.h"
# include "../defs_bonus.h"
# include "../error_exit/error_exit_bonus.h"
# include "../global/init_g_map_bonus.h"
# include "../global/init_g_map_to_check_bonus.h"

bool	is_empty_line(char *line);
void	create_map_array(char *map_first_line, int fd);
void	init_maps(void);

#endif
