// #ifndef CONSTANTS_H
// # define CONSTANTS_H

# include <math.h>
# include <stdint.h>

# include "./ft_printf/ft_printf.h"
# include "./ft_printf/libft/libft.h"

# define MAX_MAP_LEN 50

# define PI 3.14159265
# define TWO_PI 6.28318530

# define TILE_SIZE 64

# define MINIMAP_SCALE_FACTOR 0.2

// # define WINDOW_WIDTH 1280
// # define WINDOW_HEIGHT 800

# define FOV_ANGLE (60 * (PI / 180))

// # define NUM_RAYS WINDOW_WIDTH

# define DIST_PROJ_PLANE ((WINDOW_WIDTH / 2) / tan(FOV_ANGLE / 2))

typedef uint32_t t_color;

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

// #endif