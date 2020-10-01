#ifndef TEXTURES_H
# define TEXTURES_H

# include <stdint.h>
# include "defs.h"
# include "upng.h"

typedef struct	texture_s {
	upng_t		*upngTexture;
	int			width;
	int			height;
	uint32_t	*texture_buffer;
}				texture_t;

typedef enum	e_textures
{
	REDBRICK,
	PURPLESTONE,
	MOSSYSTONE,
	GRAYSTONE,
	COLORSTONE,
	BLUESTONE,
	WOOD,
	EAGLE,
	PIKUMA,

	NUM_TEXTURES
}				t_textures;

texture_t	wallTextures[NUM_TEXTURES];

void	loadWallTextures();
void	freeWallTextures();

#endif