#include <stdbool.h>

#define SUCCESS 0
#define MAX(x, y) x >= y ? x : y
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

	bool			err_flag;
	t_map			map;
}					t_data;