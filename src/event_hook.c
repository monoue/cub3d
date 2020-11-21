/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 13:43:14 by monoue            #+#    #+#             */
/*   Updated: 2020/11/21 15:59:13 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event_hook.h"

int		key_down(int keycode, void *null)
{
	(void)null;
	if (keycode == KEY_ESC)
		exit(0);
	if (keycode == KEY_W)
		g_player.walk_direction = FRONT;
	if (keycode == KEY_S)
		g_player.walk_direction = BACK;
	if (keycode == KEY_A)
		g_player.walk_direction = LEFT;
	if (keycode == KEY_D)
		g_player.walk_direction = RIGHT;
	if (keycode == KEY_LEFT)
		g_player.turn_direction = TO_LEFT;
	if (keycode == KEY_RIGHT)
		g_player.turn_direction = TO_RIGHT;
	return (0);
}

int		key_up(int keycode, void *null)
{
	(void)null;
	if (keycode == KEY_W)
		g_player.walk_direction = NEUTRAL;
	if (keycode == KEY_S)
		g_player.walk_direction = NEUTRAL;
	if (keycode == KEY_A)
		g_player.walk_direction = NEUTRAL;
	if (keycode == KEY_D)
		g_player.walk_direction = NEUTRAL;
	if (keycode == KEY_LEFT)
		g_player.turn_direction = NEUTRAL;
	if (keycode == KEY_RIGHT)
		g_player.turn_direction = NEUTRAL;
	return (0);
}

int		finish_program(void *null)
{
	(void)null;
	// free 関係？
	exit(0);
	// mlx_clear_window(g_mlx.mlx_ptr, g_mlx.win_ptr);
	// mlx_destroy_window(g_mlx.mlx_ptr, g_mlx.win_ptr);
	// mlx_destroy_image(g_mlx.mlx_ptr, g_img.img_ptr);
	return (0);
}