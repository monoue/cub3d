/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_put.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 10:41:26 by sperrin           #+#    #+#             */
/*   Updated: 2020/10/16 12:01:18 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_loop(t_env *e)
{
	e->p.camerax = 2 * e->x / (double)(e->screen.width) - 1;
	e->p.side = 0;
	e->p.rayposx = e->p.posx;
	e->p.rayposy = e->p.posy;
	e->p.raydirx = e->p.dirx + e->p.planex * e->p.camerax;
	e->p.raydiry = e->p.diry + e->p.planey * e->p.camerax;
	e->p.mapx = (int)e->p.rayposx;
	e->p.mapy = (int)e->p.rayposy;
	e->p.deltadistx = sqrt(1 + (e->p.raydiry * e->p.raydiry) /
			(e->p.raydirx * e->p.raydirx));
	e->p.deltadisty = sqrt(1 + (e->p.raydirx * e->p.raydirx) /
			(e->p.raydiry * e->p.raydiry));
	e->p.hit = 0;
}

int		rgb_int(int red, int green, int blue)
{
	int	rgb;

	rgb = red;
	rgb = (rgb << 8) + green;
	rgb = (rgb << 8) + blue;
	return (rgb);
}

int		drawline(t_env *e, int x, int text_x)
{
	int		i;
	int		*text;
	double	step;
	double	pos;

	i = -1;
	step = 1.0 * e->text_h / e->p.lineheight;
	pos = (e->p.drawstart - e->screen.height / 2 + e->p.lineheight / 2) * step;
	text = e->txt_data;
	while (++i < e->p.drawstart)
		*(e->edit + x + i * e->szl / 4) = rgb_int(e->sr, e->sg, e->sb);
	while (i <= e->p.drawend)
	{
		*(e->edit + x + i++ * e->szl / 4) = *(text + text_x +
		(int)pos * e->text_sl / 4);
		pos += step;
	}
	while (i < e->screen.height)
		*(e->edit + x + i++ * e->szl / 4) = rgb_int(e->fr, e->fg, e->fb);
	return (1);
}

void	ft_texture(int dir, char *str, t_env *e)
{
	while (*str == ' ')
		str++;
	if (dir == 1)
		e->t.txt1_path = str;
	if (dir == 2)
		e->t.txt2_path = str;
	if (dir == 3)
		e->t.txt3_path = str;
	if (dir == 4)
		e->t.txt4_path = str;
	if (dir == 5)
		e->t.spr_path = str;
}
