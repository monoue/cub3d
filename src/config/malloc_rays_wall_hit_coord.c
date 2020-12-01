/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_rays_wall_hit_coord.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 12:55:16 by monoue            #+#    #+#             */
/*   Updated: 2020/12/01 12:55:55 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc_rays_wall_hit_coord.h"

void	malloc_rays_wall_hit_coord(void)
{
	int	index;

	index = 0;
	while (index < g_config.window_width)
	{
		g_rays[index].wall_hit_coord = malloc(sizeof(t_coord));
		index++;
	}
}
