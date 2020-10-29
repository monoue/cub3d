/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 10:13:55 by monoue            #+#    #+#             */
/*   Updated: 2020/10/29 16:55:04 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx/mlx.h"
#include "init_mlx.h"

t_mlx	g_mlx;
t_img	g_img;

int		key_press(int keycode, t_data *p)
{
	t_data	*img;

	img = (t_data *)p;
	if (keycode == KEY_ESC)
		exit(0);
	else if (keycode == KEY_W && img->key.fd == 0)
		img->key.fd = 1;
	else if (keycode == KEY_S && img->key.bk == 0)
		img->key.bk = 1;
	else if (keycode == KEY_A && img->key.lt == 0)
		img->key.lt = 1;
	else if (keycode == KEY_D && img->key.rt == 0)
		img->key.rt = 1;
	else if (keycode == KEY_LEFT && img->key.rlt == 0)
		img->key.rlt = 1;
	else if (keycode == KEY_RIGHT && img->key.rrt == 0)
		img->key.rrt = 1;
	return (1);
}


// TODO: 悩んでいても進まない！　とにかく、一旦そのままなぞる！　最後にまとめてリファクタリング！

typedef struct	s_tex
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
// cubfile_data よりも、こっちに入れちゃった方が多分いい。cubfile_data にまとめる必要性は特にないのでは。
	// char	*path;
}				t_tex;


t_tex	g_textures[TEXTURES_NUM];

// TODO: これを while で回すには、cubfile_data の方をいじってやる必要がある。というか、格納先を cubfile_dataじじゃなくて
void	set_textures()
{
	size_t	texture_i;

	texture_i = 0;
	while (texture_i < TEXTURES_NUM)
	{
		
	}
	g_textures[WALL_N].img_ptr = mlx_xpm_file_to_image(g_mlx.mlx_ptr, map.n_tex_path, &g_textures[WALL_N].width, &g_textures[WALL_N].height);
	if (g_textures[WALL_N].img_ptr == NULL)
		exit();
	g_textures[WALL_N].addr = mlx_get_data_addr(g_textures[WALL_N].img_ptr,\
	&g_textures[WALL_N].bits_per_pixel, &g_textures[WALL_N].line_length,\
	&g_textures[0].endian);


	if (!(g_textures[8].img_ptr = mlx_xpm_file_to_image(g_mlx.mlx_ptr,\
	map.sprite_tex_path, &g_textures[8].width, &g_textures[8].height)))
		return (0);
	g_textures[8].addr = mlx_get_data_addr(g_textures[8].img_ptr,\
	&g_textures[8].bits_per_pixel, &g_textures[8].line_length,\
	&g_textures[0].endian);


}


void	mlx(void)
{
	g_mlx.mlx_ptr = mlx_init();
	g_mlx.win_ptr = mlx_new_window(g_mlx.mlx_ptr, g_cubfile_data.window_width, g_cubfile_data.window_height, "Monoue's cub3D");
	g_img.img_ptr = mlx_new_image(g_mlx.mlx_ptr, g_cubfile_data.window_width, g_cubfile_data.window_height);
	g_img.data = (t_color *)mlx_get_data_addr(g_img.img_ptr, &g_img.bits_per_pixel, &g_img.line_length, &g_img.endian);

	set_textures();

	mlx_hook(g_mlx.win_ptr, KEY_PRESS, KEY_PRESS_MASK, key_press, &g_img);
	mlx_hook(g_mlx.win_ptr, KEY_RELEASE, KEY_RELEASE_MASK, key_release, &g_img);
	mlx_hook(g_mlx.win_ptr, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK, finish_program(), &g_img);
	mlx_loop(g_mlx.mlx_ptr);
}