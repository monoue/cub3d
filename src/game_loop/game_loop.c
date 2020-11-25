/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 10:13:55 by monoue            #+#    #+#             */
/*   Updated: 2020/11/25 08:52:00 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_loop.h"

static void	update(void)
{
	move_player();
	cast_all_rays_to_wall();
	update_sprites_data();
}

static void	render(void)
{
	g_color = create_trgb(0, 0, 0, 0);
	draw_rectangle(
		0,
		0,
		g_cubfile_data.window_width,
		g_cubfile_data.window_height);
	render_background();
	render_sprites();
	render_mini_map();
}

int			game_loop(void *null)
{
	(void)null;
	update();
	render();
	// if (flag)
	// save_image();
	mlx_put_image_to_window(g_mlx.mlx_ptr, g_mlx.win_ptr, g_img.img_ptr, 0, 0);
	mlx_do_sync(g_mlx.mlx_ptr);
	return (0);
}
