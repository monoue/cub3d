/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 10:13:55 by monoue            #+#    #+#             */
/*   Updated: 2020/10/30 15:07:30 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx/mlx.h"
#include "init_mlx.h"

t_texture g_textures[TEXTURES_NUM];
t_mlx	g_mlx;
t_img	g_img;

// int		key_press(int keycode, t_data *p)
// {
// 	t_data	*img;

// 	img = (t_data *)p;
// 	if (keycode == KEY_ESC)
// 		exit(0);
// 	else if (keycode == KEY_W && img->key.fd == 0)
// 		img->key.fd = 1;
// 	else if (keycode == KEY_S && img->key.bk == 0)
// 		img->key.bk = 1;
// 	else if (keycode == KEY_A && img->key.lt == 0)
// 		img->key.lt = 1;
// 	else if (keycode == KEY_D && img->key.rt == 0)
// 		img->key.rt = 1;
// 	else if (keycode == KEY_LEFT && img->key.rlt == 0)
// 		img->key.rlt = 1;
// 	else if (keycode == KEY_RIGHT && img->key.rrt == 0)
// 		img->key.rrt = 1;
// 	return (1);
// }


// TODO: 悩んでいても進まない！　とにかく、一旦そのままなぞる！　最後にまとめてリファクタリング！


void	init_texture_paths()
{
	size_t	t_i;

	t_i = 0;
	while (t_i < TEXTURES_NUM)
	{
		g_textures[t_i].path = NULL;
		t_i++;
	}
}


static void	set_textures()
{
	size_t		t_i;
	t_texture	texture_i;

	t_i = 0;
	while (t_i < TEXTURES_NUM)
	{
		texture_i = g_textures[t_i];
		texture_i.img_ptr = mlx_xpm_file_to_image(g_mlx.mlx_ptr, texture_i.path, &texture_i.width, &texture_i.height);
		// TODO: エラーメッセージ、strerror で対処できるか後でやってみる
		if (texture_i.img_ptr == NULL)
			exit_with_error_message(SINGLE, "xpm file's data could not be read");
		texture_i.addr = mlx_get_data_addr(texture_i.img_ptr, &texture_i.bits_per_pixel, &texture_i.line_length, &texture_i.endian);
	}
}


void	mlx(void)
{
	g_mlx.mlx_ptr = mlx_init();
	g_mlx.win_ptr = mlx_new_window(g_mlx.mlx_ptr, g_cubfile_data.window_width, g_cubfile_data.window_height, "Monoue's cub3D");
	g_img.img_ptr = mlx_new_image(g_mlx.mlx_ptr, g_cubfile_data.window_width, g_cubfile_data.window_height);
	g_img.data = (t_color *)mlx_get_data_addr(g_img.img_ptr, &g_img.bits_per_pixel, &g_img.line_length, &g_img.endian);

	set_textures();

	// mlx_hook(g_mlx.win_ptr, KEY_PRESS, KEY_PRESS_MASK, key_press, &g_img);
	// mlx_hook(g_mlx.win_ptr, KEY_RELEASE, KEY_RELEASE_MASK, key_release, &g_img);
	// mlx_hook(g_mlx.win_ptr, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK, finish_program(), &g_img);
	// mlx_loop(g_mlx.mlx_ptr);
}