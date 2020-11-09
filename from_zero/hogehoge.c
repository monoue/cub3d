#include <stdio.h>
#include "minilibx/mlx.h"

typedef struct s_img
{
	void		*ptr;
	int			*data;
	int			width;
	int			height;


	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

int     main(void)
{
    void    *mlx;
    void    *mlx_win;
    void    *img;
    char    *relative_path = "./images/bluestone.xpm";
    int     img_width;
    int     img_height;
	mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
    img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
	mlx_put_image_to_window(mlx, mlx_win, img, 50, 50);
    mlx_loop(mlx);
}