#include <stdbool.h>

#define SUCCESS			0
#define MAX(x, y)		x >= y ? x : y
#define IMGDIR			"./images"
#define BLUESTONE_XPM	IMGDIR"/bluestone.xpm"
#define BARREL_XPM		IMGDIR"/barrel.xpm"
#define COLORSTONE_XPM	IMGDIR"/colorstone.xpm"
#define GREYSTONE_XPM	IMGDIR"/greystone.xpm"
#define REDBRICK_XPM	IMGDIR"/redbrick.xpm"

typedef enum	e_textures
{
	BLUESTONE,
	BARREL,
	COLORSTONE,
	GREYSTONE,
	REDBRICK,

	TEXTURES_NUM
}				t_textures;

typedef enum	e_error_types
{
	SINGLE,
	ID_OVERLAPPING,
	WRONG_INFO_NUM,
	INVALID_INFO,
	INVALID_PATH,
	// FD

	ERROR_TYPES_NUM
}				t_error_types;

// typedef enum	e_ids
// {
// 	RESOLUTION,
// 	NORTH_TEXTURE,
// 	EAST_TEXTURE,
// 	WEST_TEXTURE,
// 	SOUTH_TEXTURE,
// 	SPRITE_TEXTURE,
// 	FLOOR_COLOR,
// 	CEILING_COLOR,

// 	ID_NUM
// }				t_ids;

typedef struct		s_map
{
	int				window_width;
	int				window_height;
	char			*north_texture_path;
	char			*east_texture_path;
	char			*west_texture_path;
	char			*south_texture_path;
	char			*sprite_texture_path;
	int				floor_color;
	int				ceiling_color;
	// int				elements_num;
}					t_map;

extern t_map	g_map;

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
	// t_map			map;
}					t_data;
