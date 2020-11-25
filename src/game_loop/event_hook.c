/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 13:43:14 by monoue            #+#    #+#             */
/*   Updated: 2020/11/25 09:00:35 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "event_hook.h"

static int	key_down(int keycode, void *null)
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

static int	key_up(int keycode, void *null)
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

static int	finish_program(void *null)
{
	(void)null;
	exit(0);
	return (0);
}

void		event_hook(void)
{
	mlx_hook(g_mlx.win_ptr, KEY_PRESS, KEY_PRESS_MASK, key_down, NULL);
	mlx_hook(g_mlx.win_ptr, KEY_RELEASE, KEY_RELEASE_MASK, key_up, NULL);
	mlx_hook(g_mlx.win_ptr, DESTROY_NOTIFY, STRUCTURE_NOTIFY_MASK,
														finish_program, NULL);
}