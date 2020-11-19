#ifndef SAVE_BITMAP_H
# define SAVE_BITMAP_H

# include "defs.h"
# include "init_mlx.h"
# include "set_cubfile_data.h"

# define FILE_HEADER_SIZE 14
# define INFO_HEADER_SIZE 40
# define HEADER_SIZE (FILE_HEADER_SIZE + INFO_HEADER_SIZE)

typedef struct	s_rgb{
	unsigned char b;
	unsigned char g;
	unsigned char r;
}				t_rgb;

typedef struct	s_image{
	unsigned int	height;
	unsigned int	width;
	t_rgb			*data;
}				t_image;

t_image *Read_Bmp(char *filename);

int Write_Bmp(char *filename, t_image *img);

t_image *Create_Image(int width, int height);
void Free_Image(t_image *img);

void	make_screenshot();


#endif
