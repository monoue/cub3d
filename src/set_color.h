#ifndef SET_COLOR_H
# define SET_COLOR_H

# include "defs.h"
# include "error.h"

void	set_color(t_color *color, const char **infos, char *id);
t_color	create_trgb(int t, int r, int g, int b);

#endif
