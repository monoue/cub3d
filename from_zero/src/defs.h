#ifndef DEFS_H
# define DEFS_H

# include <math.h>
# include <stdint.h>

# include "./libft/libft.h"

# define MAX_MAP_LEN 50

# define PI 3.14159265
# define TWO_PI 6.28318530

# define TILE_SIZE 64

# define MINIMAP_SCALE_FACTOR 0.2

#define SUCCESS			0
#define IMGDIR			"./images"
#define BLUESTONE_XPM	IMGDIR"/bluestone.xpm"
#define BARREL_XPM		IMGDIR"/barrel.xpm"
#define COLORSTONE_XPM	IMGDIR"/colorstone.xpm"
#define GREYSTONE_XPM	IMGDIR"/greystone.xpm"
#define REDBRICK_XPM	IMGDIR"/redbrick.xpm"
#define MAX_MAP_LENGTH	50

// # define WINDOW_WIDTH 1280
// # define WINDOW_HEIGHT 800

# define FOV_ANGLE (60 * (PI / 180))

// # define NUM_RAYS WINDOW_WIDTH

# define DIST_PROJ_PLANE ((WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2))

typedef uint32_t t_color;

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
	ERRNO,
	SINGLE,
	ID_OVERLAPPING,
	WRONG_INFO_NUM,
	INVALID_INFO,
	INVALID_PATH,
	LACKING_ELEMENT,
	// FD

	ERROR_TYPES_NUM
}				t_error_types;

typedef struct		s_cubfile_data
{
	int				window_width;
	int				window_height;
	char			*north_texture_path;
	char			*east_texture_path;
	char			*west_texture_path;
	char			*south_texture_path;
	char			*sprite_texture_path;
	t_color			floor_color;
	t_color			ceiling_color;

	size_t			sprites_num;
	// int				elements_num;
	size_t			map_height;
}					t_cubfile_data;

typedef struct		s_data
{
	void			*mlx;
	void			*win;

	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;

	// int				fd;

	// bool			err_flag;
	// t_cubfile_data			map;
}					t_data;

// 要る？
# define FPS 30
// 次のフレームに達するまでに要する時間。フレーム間の時間。
// これも、要る？
# define FRAME_TIME_LENGTH (1000 / FPS)
# define SUCCESS 0
// # define SDL_ERROR 1
// # define DEFAULT_GRAPHIC_DRIVER -1
# define LEFT -1
# define RIGHT 1
# define FRONT 1
# define BACK -1
# define NEUTRAL 0

#endif