#ifndef INIT_MLX_H
# define INIT_MLX_H

# include "defs.h"
# include "set_cubfile_data.h"

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

extern	g_mlx;
extern	g_img;

#endif
