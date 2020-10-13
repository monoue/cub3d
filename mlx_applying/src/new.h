#include <unistd.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

#define ERROR -1
#define SUCCESS 0
#define SAFE_FREE(ptr) {free(ptr); ptr = NULL;}

#define WALL_N 0
#define WALL_S 1
#define WALL_W 2
#define WALL_E 3
// typedef enum
// {
// 	RESOLUTION,
// 	NORTH_TEXTURE,
// 	SOUTH_TEXTURE,
// 	WEST_TEXTURE,
// 	EAST_TEXTURE,
// 	SPRITE_TEXTURE,
// 	FLOOR_COLOR,
// 	CEILING_COLOR,

// 	TYPE_IDENTIFIERS_NUM
// } TYPE_IDENTIFIERS;
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

typedef struct		s_map
{
	int				screen_w;
	int				screen_h;
	char			*n_texture;
	char			*s_texture;
	char			*w_texture;
	char			*e_texture;
	char			*sprite_texture;
	int				ceiling_color;
	int				floor_color;
	int				elements_num;
}					t_map;

typedef struct		s_data
{
	void			*mlx;
	void			*mlx_win;
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
	bool			err_flag;
	t_ky			key;
	t_player		player;
	t_tex			tex[10];
	t_sprite		*sprite;
	t_sprite_cal	sprite_cal;
	t_texture		texture;
	t_ray			ray;
	t_map			map;
}					t_data;

void	init_map(t_data *img)
{
	img->map.screen_w = 0;
	img->map.screen_h = 0;
	img->map.n_texture = NULL;
	img->map.e_texture = NULL;
	img->map.w_texture = NULL;
	img->map.s_texture = NULL;
	img->map.sprite_texture = NULL;
	img->map.ceiling_color = 0;
	img->map.floor_color = 0;
	img->map.elements_num = 0; // 何を管理？？？
	img->err_flag = false;
}

int		put_err_msg(char *msg);
void	map_open_error(char *s, int fd);
int		get_window(t_data *img, char *r_line);
int		case_n(t_data *img, char *line);
int		get_texture_n(t_data *img, char *line);
int		get_map_info(t_data *img, char *line);
void	read_map_open(t_data *img, char *filename);
void	init_game(char *filename);