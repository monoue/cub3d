/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 10:22:35 by sperrin           #+#    #+#             */
/*   Updated: 2020/10/21 13:30:06 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx_opengl_20191021/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include <math.h>

# define MLX_BIG_ENDIAN 1
# define KEYPRESS		2
# define KEYRELEASE		3
# define KEYPRESSMASK	1L<<0
# define KEYRELEASEMASK	1L<<1

typedef struct		s_per
{
	double			posx;
	double			posy;
	double			dirx;
	double			diry;
	double			planex;
	double			planey;
	double			time;
	double			oldtime;
	double			camerax;
	double			rayposx;
	double			rayposy;
	double			raydirx;
	double			raydiry;
	double			dira;
	int				mapy;
	int				mapx;
	double			sidedisty;
	double			sidedistx;
	double			deltadistx;
	double			deltadisty;
	double			perpwalldist;
	int				stepx;
	int				stepy;
	int				hit;
	int				side;
	int				lineheight;
	int				drawstart;
	int				drawend;
	double			olddirx;
	double			olddiry;
	double			oldplanex;
	double			oldplaney;
	double			movespeed;
	double			rotspeed;
	char			walldir;
	double			wallx;
	double			zbuffer[4000];
	int				spr;
}					t_per;

typedef struct		s_screen
{
	void			*win;
	int				height;
	int				width;
}					t_screen;

typedef struct		s_text
{
	void			*txt1;
	int				*txt1_data;
	int				text1_h;
	int				text1_w;
	int				text1_sl;
	int				text1_sb;
	int				text1_ed;
	void			*txt2;
	int				*txt2_data;
	int				text2_h;
	int				text2_w;
	int				text2_sl;
	int				text2_sb;
	int				text2_ed;
	void			*txt3;
	int				*txt3_data;
	int				text3_h;
	int				text3_w;
	int				text3_sl;
	int				text3_sb;
	int				text3_ed;
	void			*txt4;
	int				*txt4_data;
	int				text4_h;
	int				text4_w;
	int				text4_sl;
	int				text4_sb;
	int				text4_ed;
	void			*txt5;
	int				*txt5_data;
	int				text5_h;
	int				text5_w;
	int				text5_sl;
	int				text5_sb;
	int				text5_ed;
	char			*txt1_path;
	char			*txt2_path;
	char			*txt3_path;
	char			*txt4_path;
	char			*spr_path;
	int				textgun_h;
	int				textgun_w;
	int				textexp_h;
	int				textexp_w;
}					t_text;

typedef	struct		s_spriteptr
{
	float			x;
	float			y;
	double			d;
}					t_spriteptr;

typedef struct		s_sprtools
{
	double			spritex;
	double			spritey;
	double			invdet;
	double			transformx;
	double			transformy;
	int				spritescreenx;
	int				spriteheight;
	int				drawstarty;
	int				drawendy;
	int				spritewidth;
	int				drawstartx;
	int				drawendx;
	int				tex_x;
	int				tex_y;
	int				x;
	int				y;
	int				d;
}					t_sprtools;

typedef struct		s_env
{
	void			*mlx;
	void			*img;
	char			**map;
	int				qwerty;
	int				bpx;
	int				szl;
	int				endiant;
	int				*edit;
	int				up;
	int				down;
	int				left;
	int				rotate_left;
	int				rotate_right;
	int				w;
	int				h;
	int				right;
	int				sprint;
	int				screenshot;
	int				sprite_hit;
	int				sprite_x;
	int				spr_h;
	int				spr_start;
	int				spr_end;
	int				*spr_order;
	int				spr_number;
	int				sr;
	int				sg;
	int				sb;
	int				fr;
	int				fg;
	int				fb;
	int				x;
	int				y;
	int				a;
	int				text_x;
	int				text_h;
	int				text_sl;
	int				*txt_data;
	int				max_x;
	int				max_y;
	int				pos;
	int				res_done;
	int				sky_done;
	int				floor_done;
	int				no_done;
	int				so_done;
	int				we_done;
	int				ea_done;
	int				s_done;
	int				spawn_done;
	int				err;
	int				bmp;
	int				fd;
	char			**map_c;
	int				flag;
	int				check;
	int				map_up;
	int				flag_1;
	t_per			p;
	t_screen		screen;
	t_text			t;
	t_sprtools		sprt;
	t_spriteptr		*sprites;
}					t_env;

int					key_hook(int keyconde, t_env *e);
void				init_player(t_env *e);
void				draw_wolf(t_env *e);
int					key_release(int keycode, t_env *e);
int					key_press(int keycode, t_env *e);
void				ft_error(int err);
void				distance_wall(t_env *e);
void				detect_wall(t_env *e);
void				ray_step(t_env *e);
void				init_loop(t_env *e);
void				ray_move(t_env *e);
void				ray_move2(t_env *e);
int					destroy_img(t_env *e);
int					expose_hook(t_env *e);
int					loop_hook(t_env *e);
void				ray_move4(t_env *e);
int					key_press3(int keycode, t_env *e);
int					ft_namecheck(char *arg, char *ext);
int					ft_savecheck(char *arg, char *save);
int					ft_bitmap(t_env *e);
int					read_file(t_env *e, char *cub);
void				choose_texture(t_env *e);
int					drawline(t_env *e, int x, int text_x);
void				ft_pos(t_env *e);
void				drawsprites(t_env *e);
void				make_screenshot(t_env *e);
int					drawline(t_env *e, int x, int text_x);
void				define_line(t_env *e);
void				txt_init(int dir, char *str, t_env *e);
int					ft_cubatoi_f(const char *str);
int					ft_cubatoi_r(const char *str);
int					ft_spaceskip(char *line, int *i);
int					ft_res(t_env *e, char *line, int *i);
int					ft_map(t_env *e, char *line, int *i);
int					ft_slist(t_env *e);
void				put_error(char *message);
int					ft_cubatoi_r(const char *str);
int					ft_cubatoi_r(const char *str);
void				check(t_env *e);
void				text_error(t_env *e);
#endif
