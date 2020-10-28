#ifndef CREATE_MAPS_H
# define CREATE_MAPS_H

# include "libft/libft.h"
# include "defs.h"
# include "error.h"


extern char	g_map[MAX_MAP_LEN + 1][MAX_MAP_LEN + 1];
extern char	g_map_to_check[MAX_MAP_LEN + 1][MAX_MAP_LEN + 1];

void	create_map_array(char *map_first_line, int fd);
void	initialize_map(void);

#endif
