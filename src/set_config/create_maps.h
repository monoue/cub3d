/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_maps.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:10:13 by monoue            #+#    #+#             */
/*   Updated: 2020/12/09 07:26:03 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CREATE_MAPS_H
# define CREATE_MAPS_H

# include "../../libft/libft.h"
# include "../defs.h"
# include "../error_exit/error_exit.h"
# include "../global/init_g_map.h"
# include "../global/init_g_map_to_check.h"

void	create_map_array(char *map_first_line, int fd);
void	init_maps(void);

#endif
