/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:25:54 by monoue            #+#    #+#             */
/*   Updated: 2020/11/09 15:42:03 by monoue           ###   ########.fr       */
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

// この関数、使っていない。
// ここから切り取って、set_texture を改修すべき。
void	set_textures(void)
{
	size_t		t_i;
	// t_texture	texture_i;

	t_i = 0;
	while (t_i < TEXTURES_NUM)
	{
		// これ、本当に動いているんだっけ？？
		// texture_i = g_textures[t_i];
		g_textures[t_i].img_ptr = mlx_xpm_file_to_image(g_mlx.mlx_ptr, g_textures[t_i].path, &g_textures[t_i].width, &g_textures[t_i].height);
		// TODO: エラーメッセージ、strerror で対処できるか後でやってみる
		if (g_textures[t_i].img_ptr == NULL)
			exit_with_error_message(SINGLE, "xpm file's data could not be read");
		g_textures[t_i].addr = mlx_get_data_addr(g_textures[t_i].img_ptr, &g_textures[t_i].bits_per_pixel, &g_textures[t_i].line_length, &g_textures[t_i].endian);
		// t_color  版（ダメ元）
		// texture_i.addr = (t_color *)mlx_get_data_addr(texture_i.img_ptr, &texture_i.bits_per_pixel, &texture_i.line_length, &texture_i.endian);
		t_i++;
	}
}