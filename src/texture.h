#ifndef TEXTURE_H
# define TEXTURE_H

typedef struct	s_texture
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	char	*path;
}				t_texture;

# include "defs.h"
# include "error.h"
# include "init_mlx.h"
# include "../minilibx/mlx.h"


extern t_texture g_textures[TEXTURES_NUM];

void	set_textures(void);
void	init_texture_paths(void);
void	set_textures(void);

#endif
