/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_line.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:36:02 by monoue            #+#    #+#             */
/*   Updated: 2020/11/24 16:36:03 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_MAP_LINE_H
# define IS_MAP_LINE_H

# include "unistd.h"
# include "stdbool.h"

bool	is_spawn_point_c(char c);
bool	is_map_line(const char *cubfile_line);

#endif
