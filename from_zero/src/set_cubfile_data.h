#ifndef SET_CUBFILE_DATA_H
# define SET_CUBFILE_DATA_H

# include "libft/libft.h"
# include "create_maps.h"
# include "player.h"
# include "check_map_error.h"
# include "set_color.h"
# include <fcntl.h>

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
	size_t			map_height;
}					t_cubfile_data;

extern t_cubfile_data g_cubfile_data;

void	set_cubfile_data(char *filename);

#endif
