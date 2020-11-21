/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:10:57 by monoue            #+#    #+#             */
/*   Updated: 2020/11/21 13:10:59 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_MAP_ERROR_H
# define CHECK_MAP_ERROR_H

# include "defs.h"
# include "create_maps.h"

void	exit_if_map_is_not_surrounded_by_walls(int current_x, int current_y);

#endif
