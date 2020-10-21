#include "texture.h"

static const char *g_texture_file_names[NUM_TEXTURES] =
{
	"./images/redbrick.png",
	"./images/purplestone.png",
	"./images/mossystone.png",
	"./images/graystone.png",
	"./images/colorstone.png",
	"./images/bluestone.png",
	"./images/wood.png",
	"./images/eagle.png",
	"./images/pikuma.png",
};

void	load_wall_textures(void)
{
	int	index;

	index = 0;
	while (index < NUM_TEXTURES)
	{
		upng_t	*upng;

		upng = upng_new_from_file(g_texture_file_names[index]);
		if (upng == NULL)
			continue ;
		upng_decode(upng);
		if (upng_get_error(upng) == UPNG_EOK)
		{
			wall_textures[index].upng_texture = upng;
			wall_textures[index].width = upng_get_width(upng);
			wall_textures[index].height = upng_get_height(upng);
			wall_textures[index].texture_buffer = (t_color*)upng_get_buffer(upng);

		}
		index++;
	}
}

void	free_wall_textures()
{
	int	index;

	index = 0;
	while (index < NUM_TEXTURES)
	{
		upng_free(wall_textures[index].upng_texture);
		index++;
	}
}