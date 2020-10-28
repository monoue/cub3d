/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 16:18:51 by monoue            #+#    #+#             */
/*   Updated: 2020/10/28 16:32:59 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check_map_error.h"

const int	g_dx[4] = {1, 0, -1, 0};
const int	g_dy[4] = {0, 1, 0, -1};

static bool	is_out_of_map(int x, int y)
{
	return (x < 0 || x >= MAX_MAP_LEN || y < 0 || y >= MAX_MAP_LEN);
}

void		exit_if_map_is_not_surrounded_by_walls(int current_x, int current_y)
{
	int		direction;
	int		new_x;
	int		new_y;
	char	new_c;

	g_map_to_check[current_y][current_x] = 'X';
	direction = 0;
	while (direction < 4)
	{
		new_x = current_x + g_dx[direction];
		new_y = current_y + g_dy[direction];
		if (is_out_of_map(new_x, new_y))
			exit_with_error_message(SINGLE, "The map is not surrounded by walls");
		new_c = g_map_to_check[new_y][new_x];
		if (new_c == '\0')
			exit_with_error_message(SINGLE, "The map is not surrounded by walls");
		if (new_c == '1' || new_c == 'X')
			;
		else
			exit_if_map_is_not_surrounded_by_walls(new_x, new_y);
		direction++;
	}
}
