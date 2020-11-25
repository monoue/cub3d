/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_maps.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:10:13 by monoue            #+#    #+#             */
/*   Updated: 2020/11/25 09:26:13 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CREATE_MAPS_H
# define CREATE_MAPS_H

# include "src/libft/libft.h"
# include "src/defs.h"
# include "src/error_exit/error_exit.h"

extern char	g_map[MAX_MAP_LEN + 1][MAX_MAP_LEN + 1];
extern char	g_map_to_check[MAX_MAP_LEN + 1][MAX_MAP_LEN + 1];

void	create_map_array(char *map_first_line, int fd);
void	init_maps(void);

#endif
