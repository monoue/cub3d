/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_g_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:52:38 by monoue            #+#    #+#             */
/*   Updated: 2020/11/26 17:06:21 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_g_textures.h"

t_texture	g_textures[TEXTURES_NUM];

void	init_texture_paths(void)
{
	size_t	index;

	index = 0;
	while (index < TEXTURES_NUM)
	{
		g_textures[index].path = NULL;
		index++;
	}
}
