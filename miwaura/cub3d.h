/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/24 12:54:26 by miwaura           #+#    #+#             */
/*   Updated: 2020/10/14 16:52:49 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./get_next_line/get_next_line.h"
# include "./minilibx_mms_20200219/mlx.h"
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>

# if defined(__APPLE__)
#  define KEY_ESC 53
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
# else
#  define KEY_A 0x0061
#  define KEY_D 0x0064
#  define KEY_S 0x0073
#  define KEY_W 0x0077
#  define KEY_LEFT 0xff51
#  define KEY_RIGHT 0xff53
#  define KEY_ESC 0xff1b
# endif
# define WALL_N 0
# define WALL_S 1
# define WALL_W 2
# define WALL_E 3
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define VMOVE 0.0

typedef struct		s_texture
{
	int				line_height;
	int				draw_start;
	int				draw_end;
	int				texnum;
	double			wall_x;
	double			step;
	double			texpos;
	int				y;
	int				tex_x;
	int				tex_y;
	int				color;
	char			*dst;
}					t_texture;

typedef struct		s_player
{
	double			p_x;
	double			p_y;
	char			dir;
	double			dir_x;
	double			dir_y;
	double			pl_x;
	double			pl_y;
	double			spd;
	double			rl_spd;
}					t_player;

typedef struct		s_map
{
	int				window_width;
	int				window_height;
	char			*n_tex_path;
	char			*e_tex_path;
	char			*w_tex_path;
	char			*s_tex_path;
	char			*sprite_tex_path;
	int				floor_color;
	int				ceiling_color;
	int				elements_num;
}					t_map;

typedef struct		s_ky
{
	int				fd;
	int				bk;
	int				rt;
	int				lt;
	int				rrt;
	int				rlt;
}					t_ky;

typedef struct		s_ray
{
	double			cm_x;
	double			ray_dir_x;
	double			ray_dir_y;
	double			sd_di_x;
	double			sd_di_y;
	double			dl_di_x;
	double			dl_di_y;
	double			p_w_di;
	int				mp_x;
	int				mp_y;
	int				st_x;
	int				st_y;
	int				hit;
	int				side;
	int				line_h;
	int				dw_start;
	int				dw_end;
}					t_ray;

typedef struct		s_tex
{
	void			*img_ptr;
	char			*addr;
	int				b_per_pix;
	int				line_length;
	int				endian;
	int				w;
	int				h;
}					t_tex;

typedef struct		s_sprite
{
	int				x;
	int				y;
	double			distance;
	int				order;
	int				texture;
	double			angle;
}					t_sprite;

typedef struct		s_sprite_cal{
	double			sprite_x;
	double			sprite_y;
	double			invdet;
	double			trans_x;
	double			trans_y;
	int				screen_x;
	int				vmscreen;
	int				sprite_h;
	int				dw_start_y;
	int				dw_end_y;
	int				sprite_w;
	int				dw_start_x;
	int				dw_end_x;
}					t_sprite_cal;

typedef struct		s_data
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				fd;
	char			**w_map;
	char			**w_map_c;
	double			*zbuffer;
	int				sprite_num;
	int				flag;
	t_ky			key;
	t_player		player;
	t_tex			tex[10];
	t_sprite		*sprite;
	t_sprite_cal	sprite_cal;
	t_texture		texture;
	t_ray			ray;
	t_map			map;
}					t_data;

int					set_textures(t_data *img);
void				sprite_init(t_data *img);
void				ray_init(int x, int w, t_data *img);
void				header_init(char *cont, int width, int height);
void				header_data(t_data img, char *cont, int width, int height);
void				write_image(t_data img);
void				save_picture(char *file);
void				player(t_data *img);
void				key(t_data *img);
void				zbuffer_init(t_data *img);
void				ray_collison_texture(t_data *img, int x);
void				sprites(t_data *img, int x);
void				sort_sprite(t_data *img);
void				read_map_open(t_data *img, char *file);
void				move_right(t_data *img);
void				move_left(t_data *img);
void				move_back(t_data *img);
void				move_front(t_data *img);
void				roll_right(t_data *img);
void				roll_left(t_data *img);
void				cal_hit_wall(t_data *img);
void				cal_hit(t_data *img);
void				cal_collision(t_data *img);
int					key_pressed(int keycode, t_data *p);
int					key_released(int keycode, void *p);
void				cal_hit(t_data *img);
void				read_map_open(t_data *img, char *file);
void				map_init(t_data *img);
int					get_cubfile_info(t_data *img, char *line);
int					get_colors(t_data *img, char *line, char c);
int					get_sprite(t_data *img, char *line);
int					get_texture_n(t_data *img, char *line);
int					get_texture_s(t_data *img, char *line);
int					get_texture_w(t_data *img, char *line);
int					get_texture_e(t_data *img, char *line);
void				my_mlx_pixel_put(t_data *img, int x, int y, int color);
void				texture_celling_floor(t_data *img, int x);
void				texture_wall(t_data *img, int x);
void				texture_start_end(t_data *img);
void				texture_cal(t_data *img, int x);
void				moves(t_data *img);
void				ray_cast(t_data *img, int x);
void				sprites(t_data *img, int x);
int					render_next_frame(void *p);
int					put_err_msg(char *s);
void				exit_failure_closing_fd(char *s, int fd);
int					get_resolution(t_data *img, char *line);
void				sprite_calculation(t_data *img, int x);
void				get_inf_sprite_pos(t_data *img);
void				moves(t_data *img);
int					line_check(char *line);
char				*ft_strjoin_with_n(char *map, char *line);
int					get_map(t_data *img, char *line);
int					get_colors(t_data *img, char *line, char c);
int					get_colors_num(char *line, int i, int *sum);
void				set_py(t_data *img);
void				check(t_data *img);
void				s_texture_set(t_data *img, char *ptr, char *path);
void				e_texture_set(t_data *img, char *ptr, char *path);
void				w_texture_set(t_data *img, char *ptr, char *path);
void				n_texture_set(t_data *img, char *ptr, char *path);
void				free_reads(t_data *img);
int					case_n(t_data *img, char *line, int i, char *ptr);
int					get_texture_n(t_data *img, char *line);
int					case_s(t_data *img, char *line, int i, char *ptr);
int					get_texture_s(t_data *img, char *line);
int					case_w(t_data *img, char *line, int i, char *ptr);
int					finish_program(t_data *img);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *haystack,\
					const char *needle, size_t len);
char				**ft_split(char const *s, char c);
char				*ft_strdup(const char *s1);
int					ft_atoi(const char *str);
int					ft_isdigit(int c);
void				*ft_memcpy(void *restrict dst,\
					const void *restrict src, size_t n);
char				*ft_strchr(const char *s, int c);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlen(const char *str);
void				error_map(char *s, char *line, char *map);
int					mapline(char *line);
#endif
