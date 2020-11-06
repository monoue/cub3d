#ifndef DEFS_H
# define DEFS_H

# include <math.h>
# include <stdint.h>

# include "./libft/libft.h"

# define SUCCESS				0
# define HALF_PI				1.57079633
# define TWO_PI					6.28318530
# define PI						3.14159265
# define TWO_PI					6.28318530
# define TILE_SIZE				64
# define MAX_MAP_LEN			50
# define MINIMAP_SCALE_FACTOR	0.4
# define IMGDIR					"./images"
# define FOV_ANGLE				(60 * (PI / 180))
// # define DIST_PROJ_PLANE		((WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2))
# define NUM_RAYS				300
# define MAX_WINDOW_WIDTH		3840
// # define NUM_RAYS				5
// # define NUM_RAYS WINDOW_WIDTH
// # define TEXTURE_WIDTH			64
// # define TEXTURE_HEIGHT			64
# define FPS 30
# define FRAME_TIME_LENGTH (1000 / FPS)

typedef uint32_t t_color;

typedef enum	e_move_directions
{
	NEUTRAL,
	RIGHT,
	BACK,
	LEFT,
	FRONT,

	WALK_DIRECTIONS_NUM
}				t_move_directions;

# define TO_LEFT -1
# define TO_RIGHT 1

typedef enum	e_textures
{
	NORTH,
	EAST,
	WEST,
	SOUTH,
	SPRITE,

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



// 要る？
# define FPS 30
// 次のフレームに達するまでに要する時間。フレーム間の時間。
// これも、要る？
# define FRAME_TIME_LENGTH (1000 / FPS)
# define SUCCESS 0
// # define SDL_ERROR 1
// # define DEFAULT_GRAPHIC_DRIVER -1
// # define LEFT -1
// # define RIGHT 1
// # define FRONT 1
// # define BACK -1
# define NEUTRAL 0

#endif

// こんな感じ？
// const char *g_texture_file_names[TEXTURES_NUM] =
// {
// 	BLUESTONE_XPM,
// 	BARREL_XPM,
// 	COLORSTONE_XPM,
// 	GREYSTONE_XPM,
// 	REDBRICK_XPM
// };
// const char *g_ids[ID_NUM] =
// {
// 	"R",
// 	"NO",
// 	"EA",
// 	"WE",
// 	"SO",
// 	"S",
// 	"F",
// 	"C",
// };

// #define BLUESTONE_XPM	IMGDIR"/bluestone.xpm"
// #define BARREL_XPM		IMGDIR"/barrel.xpm"
// #define COLORSTONE_XPM	IMGDIR"/colorstone.xpm"
// #define GREYSTONE_XPM	IMGDIR"/greystone.xpm"
// #define REDBRICK_XPM	IMGDIR"/redbrick.xpm"

// typedef enum	e_textures
// {
// 	BLUESTONE,
// 	BARREL,
// 	COLORSTONE,
// 	GREYSTONE,
// 	REDBRICK,

// 	TEXTURES_NUM
// }				t_textures;