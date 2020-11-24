/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:25:54 by monoue            #+#    #+#             */
/*   Updated: 2020/11/24 09:12:24 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture.h"

t_texture g_textures[TEXTURES_NUM];

void	init_texture_paths(void)
{
	size_t	t_i;

	t_i = 0;
	while (t_i < TEXTURES_NUM)
	{
		g_textures[t_i].path = NULL;
		t_i++;
	}
}

void	set_textures(void)
{
	size_t		t_i;

	t_i = 0;
	while (t_i < TEXTURES_NUM)
	{
		g_textures[t_i].img_ptr = mlx_xpm_file_to_image(
			g_mlx.mlx_ptr,
			g_textures[t_i].path,
			&g_textures[t_i].width,
			&g_textures[t_i].height);
		if (g_textures[t_i].img_ptr == NULL)
			exit_with_error_message(ERRNO, NULL);
		g_textures[t_i].addr = mlx_get_data_addr(
			g_textures[t_i].img_ptr,
			&g_textures[t_i].bits_per_pixel,
			&g_textures[t_i].line_length,
			&g_textures[t_i].endian);
		t_i++;
	}
}
