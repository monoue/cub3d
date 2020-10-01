#include "texture.h"

static const char *textureFileNames[NUM_TEXTURES] =
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

void	loadWallTextures(void)
{
	int	index;

	index = 0;
	while (index < NUM_TEXTURES)
	{
		upng_t	*upng;

		upng = upng_new_from_file(textureFileNames[index]);
		if (upng == NULL)
			continue ;
		upng_decode(upng);
		if (upng_get_error(upng) == UPNG_EOK)
		{
			wallTextures[index].upngTexture = upng;
			wallTextures[index].width = upng_get_width(upng);
			wallTextures[index].height = upng_get_height(upng);
			wallTextures[index].texture_buffer = (uint32_t*)upng_get_buffer(upng);

		}
		index++;
	}
}

void	freeWallTextures()
{
	int	index;

	index = 0;
	while (index < NUM_TEXTURES)
	{
		upng_free(wallTextures[index].upngTexture);
		index++;
	}
}