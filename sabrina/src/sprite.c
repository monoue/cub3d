/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/28 11:32:10 by sperrin           #+#    #+#             */
/*   Updated: 2020/10/05 10:34:26 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_sprites(t_env *e)
{
	double		distance[e->p.spr];
	int			tmp;
	int			disttmp;
	int			i;

	i = -1;
	while (++i < e->p.spr)
	{
		e->spr_order[i] = i;
		distance[i] = ((e->p.posx - e->sprites[i].x) * (e->p.posx -
		e->sprites[i].x) + (e->p.posy - e->sprites[i].y) * (e->p.posy -
		e->sprites[i].y));
	}
	i = -1;
	while (++i < e->p.spr - 1)
		if (distance[i] < distance[i + 1])
		{
			disttmp = distance[i];
			distance[i] = distance[i + 1];
			distance[i + 1] = disttmp;
			tmp = e->spr_order[i];
			e->spr_order[i] = e->spr_order[i + 1];
			e->spr_order[i + 1] = tmp;
			i = -1;
		}
}

void	sprite_height(t_sprtools *sprite, t_env *e)
{
	sprite->spriteheight = abs((int)(e->screen.height / (sprite->transformy)));
	sprite->drawstarty = -sprite->spriteheight / 2 + e->screen.height / 2;
	if (sprite->drawstarty < 0)
		sprite->drawstarty = 0;
	sprite->drawendy = sprite->spriteheight / 2 + e->screen.height / 2;
	if (sprite->drawendy >= e->screen.height)
		sprite->drawendy = e->screen.height;
}

void	sprite_width(t_sprtools *sprite, t_env *e)
{
	sprite->spritewidth = abs((int)(e->screen.height / (sprite->transformy)));
	sprite->drawstartx = -sprite->spritewidth / 2 + sprite->spritescreenx;
	if (sprite->drawstartx < 0)
		sprite->drawstartx = 0;
	sprite->drawendx = sprite->spritewidth / 2 + sprite->spritescreenx;
	if (sprite->drawendx >= e->screen.width)
		sprite->drawendx = e->screen.width;
}

void	drawspritelines(t_sprtools *sprite, t_env *e)
{
	sprite->x = sprite->drawstartx;
	while (sprite->x < sprite->drawendx)
	{
		sprite->tex_x = (int)((sprite->x - (-sprite->spritewidth / 2 +
		sprite->spritescreenx)) * e->t.text5_w / sprite->spritewidth);
		sprite->y = sprite->drawstarty;
		if (sprite->transformy > 0 && sprite->x > 0 &&
		sprite->x < e->screen.width &&
		sprite->transformy < (float)e->p.zbuffer[sprite->x])
			while (sprite->y < sprite->drawendy)
			{
				sprite->d = (sprite->y) * 256 - e->screen.height * 128 +
				sprite->spriteheight * 128;
				sprite->tex_y = ((sprite->d * e->t.text5_h) /
				sprite->spriteheight) / 256;
				if (*(e->t.txt5_data + sprite->tex_x + sprite->tex_y *
				e->t.text5_sl / 4))
					*(e->edit + sprite->x + sprite->y *
					e->szl / 4) = *(e->t.txt5_data +
					sprite->tex_x + sprite->tex_y * e->t.text5_sl / 4);
				sprite->y++;
			}
		sprite->x++;
	}
}

void	drawsprites(t_env *e)
{
	int			i;
	t_spriteptr	sprite_ptr;
	t_sprtools	sprite;

	sort_sprites(e);
	i = 0;
	while (i < e->p.spr)
	{
		sprite_ptr = e->sprites[e->spr_order[i++]];
		sprite.spritex = (sprite_ptr.x) - e->p.posx;
		sprite.spritey = (sprite_ptr.y) - e->p.posy;
		sprite.invdet = 1.0 / (e->p.planex *
		e->p.diry - e->p.dirx * e->p.planey);
		sprite.transformx = sprite.invdet * (e->p.diry *
		sprite.spritex - e->p.dirx * sprite.spritey);
		sprite.transformy = sprite.invdet *
		(-e->p.planey * sprite.spritex + e->p.planex * sprite.spritey);
		sprite.spritescreenx = (int)((e->screen.width / 2) *
		(1 + sprite.transformx / sprite.transformy));
		sprite_height(&sprite, e);
		sprite_width(&sprite, e);
		drawspritelines(&sprite, e);
	}
}
