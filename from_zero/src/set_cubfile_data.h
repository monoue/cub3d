#ifndef SET_CUBFILE_DATA_H
# define SET_CUBFILE_DATA_H

# include <fcntl.h>

# include "check_map_error.h"
# include "create_maps.h"
# include "init_mlx.h"
# include "libft/libft.h"
# include "player.h"
# include "set_color.h"
# include "sprite.h"

typedef struct	s_cubfile_data
{
	int			window_width;
	int			window_height;
	t_color		floor_color;
	t_color		ceiling_color;
	size_t		sprites_num;
}				t_cubfile_data;

extern t_cubfile_data g_cubfile_data;

void	set_cubfile_data(char *filename);

#endif
