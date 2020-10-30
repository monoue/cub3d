#ifndef INIT_MLX_H
# define INIT_MLX_H

# include "defs.h"
# include "set_cubfile_data.h"
# include "player.h"

/*
** X11 events
*/
# define KEY_PRESS		2
# define KEY_RELEASE	3
# define DESTROY_NOTIFY	17	

/*
** X11 masks
*/
# define KEY_PRESS_MASK			1L << 0
# define KEY_RELEASE_MASK		1L << 1
# define STRUCTURE_NOTIFY_MASK	1L << 17

/*
** Mac OS key codes
*/
# define KEY_ESC	53
# define KEY_W		13
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2
# define KEY_LEFT	123	
# define KEY_RIGHT	124	

typedef struct	s_texture
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
// cubfile_data よりも、こっちに入れちゃった方が多分いい。cubfile_data にまとめる必要性は特にないのでは。
	char	*path;
}				t_texture;

extern t_texture g_textures[TEXTURES_NUM];

typedef struct	s_img
{
	void	*img_ptr;
	t_color	*data;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct	s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_mlx;

extern	t_mlx g_mlx;
extern	t_img g_img;

void	mlx(void);
void	init_texture_paths();

#endif
