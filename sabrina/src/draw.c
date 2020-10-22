/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 10:41:14 by sperrin           #+#    #+#             */
/*   Updated: 2020/10/16 12:30:13 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ray_move(t_env *e)
{
	e->p.movespeed = 0.05 * e->sprint;
	e->p.rotspeed = 0.05;
	if (e->up == 1)
	{
		if (e->map[(int)(e->p.posy + e->p.diry * e->p.movespeed)]
				[(int)(e->p.posx)] != '1')
			e->p.posy += e->p.diry * e->p.movespeed;
		if (e->map[(int)(e->p.posy)]
				[(int)(e->p.posx + e->p.dirx * e->p.movespeed)] != '1')
			e->p.posx += e->p.dirx * e->p.movespeed;
	}
	if (e->down == 1)
	{
		if (e->map[(int)(e->p.posy - e->p.diry * e->p.movespeed)]
				[(int)(e->p.posx)] != '1')
			e->p.posy -= e->p.diry * e->p.movespeed;
		if (e->map[(int)(e->p.posy)]
				[(int)(e->p.posx - e->p.dirx * e->p.movespeed)] != '1')
			e->p.posx -= e->p.dirx * e->p.movespeed;
	}
}

void		ray_move2(t_env *e)
{
	if (e->rotate_left == 1)
	{
		e->p.olddiry = e->p.diry;
		e->p.diry = e->p.diry * cos(e->p.rotspeed) - e->p.dirx *
			sin(e->p.rotspeed);
		e->p.dirx = e->p.olddiry * sin(e->p.rotspeed) + e->p.dirx *
			cos(e->p.rotspeed);
		e->p.oldplaney = e->p.planey;
		e->p.planey = e->p.planey * cos(e->p.rotspeed) -
			e->p.planex * sin(e->p.rotspeed);
		e->p.planex = e->p.oldplaney * sin(e->p.rotspeed) +
			e->p.planex * cos(e->p.rotspeed);
	}
	if (e->left == 1)
	{
		if (e->map[(int)e->p.posy]
		[(int)(e->p.posx - e->p.planex * e->p.movespeed)] != '1')
			e->p.posx -= e->p.planex * e->p.movespeed;
		if (e->map[(int)(e->p.posy - e->p.planey * e->p.movespeed)]
		[(int)e->p.posx] != '1')
			e->p.posy -= e->p.planey * e->p.movespeed;
	}
}

void		ray_move3(t_env *e)
{
	if (e->rotate_right == 1)
	{
		e->p.olddiry = e->p.diry;
		e->p.diry = e->p.diry * cos((e->p.rotspeed * -1)) -
			e->p.dirx * sin((e->p.rotspeed * -1));
		e->p.dirx = e->p.olddiry * sin((e->p.rotspeed * -1)) +
			e->p.dirx * cos((e->p.rotspeed * -1));
		e->p.oldplaney = e->p.planey;
		e->p.planey = e->p.planey * cos((e->p.rotspeed * -1)) -
			e->p.planex * sin((e->p.rotspeed * -1));
		e->p.planex = e->p.oldplaney * sin((e->p.rotspeed * -1)) +
			e->p.planex * cos((e->p.rotspeed * -1));
	}
	if (e->right == 1)
	{
		if (e->map[(int)e->p.posy]
		[(int)(e->p.posx + e->p.planex * e->p.movespeed)] != '1')
			e->p.posx += e->p.planex * e->p.movespeed;
		if (e->map[(int)(e->p.posy + e->p.planey * e->p.movespeed)]
		[(int)e->p.posx] != '1')
			e->p.posy += e->p.planey * e->p.movespeed;
	}
}

void		before(t_env *e)
{
	if (e->p.side == 0)
		e->p.wallx = e->p.posy + e->p.perpwalldist * e->p.raydiry;
	else
		e->p.wallx = e->p.posx + e->p.perpwalldist * e->p.raydirx;
	e->p.wallx -= floor(e->p.wallx);
	e->text_x = e->p.wallx * (e->text_sl / 4);
	if (e->p.side == 0 && e->p.dirx > 0)
		e->text_x = (e->text_sl / 4) - e->text_x - 1;
	else if (e->p.side == 1 && e->p.diry < 0)
		e->text_x = (e->text_sl / 4) - e->text_x - 1;
}

void		draw_wolf(t_env *e)
{
	e->x = 0;
	while (e->x < e->screen.width)
	{
		init_loop(e);
		ray_step(e);
		while (e->p.hit == 0)
			detect_wall(e);
		distance_wall(e);
		define_line(e);
		choose_texture(e);
		before(e);
		drawline(e, e->x, e->text_x);
		e->x++;
	}
	drawsprites(e);
	if (e->screenshot == 0)
	{
		ray_move(e);
		ray_move2(e);
		ray_move3(e);
		mlx_put_image_to_window(e->mlx, e->screen.win, e->img, 0, 0);
	}
}
