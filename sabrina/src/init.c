/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 10:41:37 by sperrin           #+#    #+#             */
/*   Updated: 2020/10/12 18:52:15 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		init_player2(t_env *e)
{
	e->mlx = NULL;
	e->screen.win = NULL;
	e->img = NULL;
	e->edit = NULL;
	e->screen.width = 0;
	e->screen.height = 0;
	e->fr = -1;
	e->fg = -1;
	e->fb = -1;
	e->sr = -1;
	e->sg = -1;
	e->sb = -1;
	e->res_done = 0;
	e->sky_done = 0;
	e->floor_done = 0;
	e->no_done = 0;
	e->so_done = 0;
	e->we_done = 0;
	e->ea_done = 0;
	e->s_done = 0;
	e->spawn_done = 0;
	e->map_up = 0;
}

void		init_player(t_env *e)
{
	e->p.dirx = -1;
	e->qwerty = 1;
	e->p.diry = 0;
	e->sprint = 1;
	e->p.planex = 0;
	e->p.planey = 0.66;
	e->p.time = 0;
	e->p.oldtime = 0;
	e->p.mapx = 0;
	e->p.mapy = 0;
	e->up = 0;
	e->down = 0;
	e->right = 0;
	e->left = 0;
	init_player2(e);
}

void		txt_init3(int dir, char *str, t_env *e)
{
	if (dir == 4)
	{
		if (e->ea_done)
			put_error("ERROR\nDUPLICATE TEXTURES DUDE\n");
		e->ea_done = 1;
		e->t.txt4 = mlx_xpm_file_to_image(e->mlx, str,
		&(e->t.text4_w), &(e->t.text4_h));
		e->t.txt4_data = (int *)mlx_get_data_addr(e->t.txt4,
		&e->t.text4_sb, &e->t.text4_sl, &e->t.text4_ed);
	}
	if (dir == 5)
	{
		if (e->s_done)
			put_error("ERROR\nDUPLICATE TEXTURES DUDE\n");
		e->s_done = 1;
		e->t.txt5 = mlx_xpm_file_to_image(e->mlx, str,
		&(e->t.text5_w), &(e->t.text5_h));
		e->t.txt5_data = (int *)mlx_get_data_addr(e->t.txt5,
		&e->t.text5_sb, &e->t.text5_sl, &e->t.text5_ed);
	}
}

void		txt_init2(int dir, char *str, t_env *e)
{
	if (dir == 3)
	{
		if (e->we_done)
			put_error("ERROR\nDUPLICATE TEXTURES DUDE\n");
		e->we_done = 1;
		e->t.txt3 = mlx_xpm_file_to_image(e->mlx, str,
		&(e->t.text3_w), &(e->t.text3_h));
		e->t.txt3_data = (int *)mlx_get_data_addr(e->t.txt3,
		&e->t.text3_sb, &e->t.text3_sl, &e->t.text3_ed);
	}
	if (dir == 2)
	{
		if (e->so_done)
			put_error("ERROR\nDUPLICATE TEXTURES DUDE\n");
		e->so_done = 1;
		e->t.txt2 = mlx_xpm_file_to_image(e->mlx, str,
		&(e->t.text2_w), &(e->t.text2_h));
		e->t.txt2_data = (int *)mlx_get_data_addr(e->t.txt2,
		&e->t.text2_sb, &e->t.text2_sl, &e->t.text2_ed);
	}
	txt_init3(dir, str, e);
}

void		txt_init(int dir, char *str, t_env *e)
{
	int fd;

	while (*str == ' ')
		str++;
	if ((fd = open(str, O_RDONLY)) < 0)
		put_error("ERROR\nWRONG TEXTURE PATH INPUT\n");
	close(fd);
	if (dir == 1)
	{
		if (e->no_done)
			put_error("ERROR\nDUPLICATE TEXTURES DUDE\n");
		e->no_done = 1;
		e->t.txt1 = mlx_xpm_file_to_image(e->mlx, str,
		&(e->t.text1_w), &(e->t.text1_h));
		e->t.txt1_data = (int *)mlx_get_data_addr(e->t.txt1, &e->t.text1_sb,
		&e->t.text1_sl, &e->t.text1_ed);
	}
	txt_init2(dir, str, e);
}
