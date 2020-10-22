/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 10:41:44 by sperrin           #+#    #+#             */
/*   Updated: 2020/10/12 18:18:09 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				key_press3(int keycode, t_env *e)
{
	if (keycode == 123)
		e->rotate_left = 1;
	else if (keycode == 124)
		e->rotate_right = 1;
	return (0);
}

int				key_press2(int keycode, t_env *e)
{
	if (keycode == 2)
		e->right = 1;
	if (keycode == 1)
		e->down = 1;
	if (keycode == 257)
		e->sprint = e->sprint * 10;
	key_press3(keycode, e);
	return (0);
}

int				key_press(int keycode, t_env *e)
{
	if (keycode == 53)
		destroy_img(e);
	if (keycode == 48)
	{
		e->up = 0;
		e->left = 0;
		e->qwerty = (e->qwerty == 1) ? 0 : 1;
	}
	if (e->qwerty == 1)
	{
		if (keycode == 13)
			e->up = 1;
		if (keycode == 0)
			e->left = 1;
	}
	else
	{
		if (keycode == 6)
			e->up = 1;
		if (keycode == 12)
			e->left = 1;
	}
	key_press2(keycode, e);
	return (0);
}

int				key_release2(int keycode, t_env *e)
{
	if (keycode == 257)
		e->sprint = e->sprint / 10;
	if (keycode == 123)
		e->rotate_left = 0;
	else if (keycode == 124)
		e->rotate_right = 0;
	return (0);
}

int				key_release(int keycode, t_env *e)
{
	if (e->qwerty == 1)
	{
		if (keycode == 13)
			e->up = 0;
		if (keycode == 0)
			e->left = 0;
	}
	else
	{
		if (keycode == 6)
			e->up = 0;
		if (keycode == 12)
			e->left = 0;
	}
	if (keycode == 2)
		e->right = 0;
	if (keycode == 1)
		e->down = 0;
	if (keycode == 49)
	{
		e->w = -100;
		e->h = -100;
	}
	key_release2(keycode, e);
	return (0);
}
