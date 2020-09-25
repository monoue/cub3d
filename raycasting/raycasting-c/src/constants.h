#ifndef CONSTANTS_H
# define CONSTANTS_H

# include <SDL2/SDL.h>
# include <math.h>
# include "./ft_printf/ft_printf.h"
# include "./ft_printf/libft/libft.h"

# define SUCCESS 0
# define SDL_ERROR 1
# define DEFAULT_GRAPHIC_DRIVER -1
# define LEFT -1
# define RIGHT 1
# define FRONT 1
# define BACK -1
# define NEUTRAL 0

# define PI 3.14159265
# define TWO_PI 6.28318530

# define TILE_SIZE 64
# define MAP_NUM_ROWS 13
# define MAP_NUM_COLS 20

# define MINIMAP_SCALE_FACTOR 1.0

# define EDGE_COLOR 255
# define INNER_COLOR 0

# define WINDOW_WIDTH (MAP_NUM_COLS * TILE_SIZE)
# define WINDOW_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)

# define FOV_ANGLE (60 * (PI / 180))

# define NUM_RAYS WINDOW_WIDTH

# define FPS 10
// 次のフレームに達するまでに要する時間。フレーム間の時間。
# define FRAME_TIME_LENGTH (1000 / FPS)

#endif