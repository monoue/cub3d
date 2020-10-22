/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 13:48:30 by sperrin           #+#    #+#             */
/*   Updated: 2020/10/05 10:34:13 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ray_step(t_env *e)
{
	if (e->p.raydirx < 0)
	{
		e->p.stepx = -1;
		e->p.sidedistx = (e->p.rayposx - e->p.mapx) * e->p.deltadistx;
	}
	else
	{
		e->p.stepx = 1;
		e->p.sidedistx = (e->p.mapx + 1.0 - e->p.rayposx) * e->p.deltadistx;
	}
	if (e->p.raydiry < 0)
	{
		e->p.stepy = -1;
		e->p.sidedisty = (e->p.rayposy - e->p.mapy) * e->p.deltadisty;
	}
	else
	{
		e->p.stepy = 1;
		e->p.sidedisty = (e->p.mapy + 1.0 - e->p.rayposy) * e->p.deltadisty;
	}
}

void		detect_wall(t_env *e)
{
	if (e->p.sidedistx < e->p.sidedisty)
	{
		e->p.sidedistx += e->p.deltadistx;
		e->p.mapx += e->p.stepx;
		e->p.side = 0;
	}
	else
	{
		e->p.sidedisty += e->p.deltadisty;
		e->p.mapy += e->p.stepy;
		e->p.side = 1;
	}
	if (e->map[e->p.mapy][e->p.mapx] == '1')
		e->p.hit = 1;
}

void		distance_wall(t_env *e)
{
	if (e->p.side == 0)
	{
		if (e->p.mapx < e->p.posx)
			e->p.walldir = 'W';
		else
			e->p.walldir = 'E';
		e->p.perpwalldist = fabs((e->p.mapx - e->p.rayposx + (1 - e->p.stepx)
					/ 2) / e->p.raydirx);
		e->p.wallx = e->p.posx + e->p.perpwalldist * e->p.dirx;
	}
	else
	{
		if (e->p.mapy < e->p.posy)
			e->p.walldir = 'N';
		else
			e->p.walldir = 'S';
		e->p.perpwalldist = fabs((e->p.mapy - e->p.rayposy + (1 - e->p.stepy)
					/ 2) / e->p.raydiry);
		e->p.wallx = e->p.posy + e->p.perpwalldist * e->p.diry;
	}
	e->p.zbuffer[e->x] = e->p.perpwalldist;
}

void		define_line(t_env *e)
{
	e->p.lineheight = (int)(e->screen.height / e->p.perpwalldist);
	e->p.drawstart = (e->p.lineheight * -1) / 2 + e->screen.height / 2;
	if (e->p.drawstart < 0)
		e->p.drawstart = 0;
	e->p.drawend = e->p.lineheight / 2 + e->screen.height / 2;
	if (e->p.drawend >= e->screen.height)
		e->p.drawend = e->screen.height - 1;
}

void		choose_texture(t_env *e)
{
	if (e->p.walldir == 'N')
	{
		e->txt_data = e->t.txt1_data;
		e->text_sl = e->t.text1_sl;
		e->text_h = e->t.text1_h;
	}
	else if (e->p.walldir == 'S')
	{
		e->txt_data = e->t.txt2_data;
		e->text_sl = e->t.text2_sl;
		e->text_h = e->t.text2_h;
	}
	else if (e->p.walldir == 'E')
	{
		e->txt_data = e->t.txt3_data;
		e->text_sl = e->t.text3_sl;
		e->text_h = e->t.text3_h;
	}
	else
	{
		e->txt_data = e->t.txt4_data;
		e->text_sl = e->t.text4_sl;
		e->text_h = e->t.text4_h;
	}
}
