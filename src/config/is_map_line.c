/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 12:41:27 by monoue            #+#    #+#             */
/*   Updated: 2020/11/30 12:41:28 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "is_map_line.h"

bool		is_spawn_point_c(char c)
{
	return (c == 'N' || c == 'E' || c == 'W' || c == 'S');
}

static bool	is_map_c(char c)
{
	return ((c >= '0' && c <= '2') || is_spawn_point_c(c) || c == ' ');
}

bool		is_map_line(const char *config_line)
{
	size_t	index;

	index = 0;
	while (config_line[index] == ' ')
		index++;
	if (config_line[index] == '\0')
		return (false);
	while (is_map_c(config_line[index]))
		index++;
	return (config_line[index] == '\0');
}
