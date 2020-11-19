#ifndef SAVE_BITMAP_H
# define SAVE_BITMAP_H

# include "defs.h"
# include "init_mlx.h"
# include "set_cubfile_data.h"

# define FILE_HEADER_SIZE 14
# define INFO_HEADER_SIZE 40
# define HEADER_SIZE (FILE_HEADER_SIZE + INFO_HEADER_SIZE)

# define FILE_TYPE_1	0
# define FILE_TYPE_2	1
# define FILE_SIZE		2
# define RESERVED_1		6
# define RESERVED_2		8
# define OFFSET_TO_PIXEL_DATA	10
# define INFO_DATA_SIZE 14
# define IMAGE_WIDTH	18
# define IMAGE_HEIGHT	22
# define PLANES			26
# define BITS_PER_PIXEL	28
# define COMPRESSION_METHOD	30
# define IMAGE_SIZE		34
# define HORZ_RESOLUTION	38
# define VERT_RESOLUTION	42
# define TOTAL_COLORS		46
# define IMPORTANT_COLORS	50

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
