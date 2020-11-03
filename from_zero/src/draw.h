#ifndef DRAW_H
# define DRAW_H

# include <unistd.h>
# include "defs.h"
# include "init_mlx.h"

void	draw_pixel(int x, int y, t_color color);
void	draw_rectangle(size_t start_x, size_t start_y, size_t width, size_t height, t_color color);
void	draw_line(int x0, int y0, int x1, int y1, t_color color);

#endif
