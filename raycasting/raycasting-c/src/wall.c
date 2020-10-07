#include "wall.h"


void	renderWallProjection(void)
{
	int		ray_i;
	int		wallStripHeight;
	float	projectedWallHeight;
	int		wallTopPixel;
	int		wallBottomPixel;
	int		y;
	float	correctDistance;
	int		textureOffsetX;
	int		textureOffsetY;
	uint32_t	texelColor;
	int		distanceFromTop;
	int		texture_width;
	int		texture_height;

	ray_i = 0;
	while (ray_i < NUM_RAYS)
	{
		correctDistance = rays[ray_i].distance * cos(rays[ray_i].rayAngle - player.rotationAngle);
		// 三角形の相似で縮小。TILE_SIZE は、実際の壁の高さ。
		projectedWallHeight = (TILE_SIZE / correctDistance) * DIST_PROJ_PLANE;
		wallStripHeight = (int)projectedWallHeight;
		wallTopPixel = (WINDOW_HEIGHT / 2) - (wallStripHeight / 2);
		if (wallTopPixel < 0)
			wallTopPixel = 0;
		wallBottomPixel = (WINDOW_HEIGHT / 2) + (wallStripHeight / 2);
		if (wallBottomPixel > WINDOW_HEIGHT)
			wallBottomPixel = WINDOW_HEIGHT;
		y = 0;
		while (y < wallTopPixel)
		{
			drawPixel(ray_i, y, 0xFF444444);
			y++;
		}

		if (rays[ray_i].wasHitVertical)
			textureOffsetX = (int)rays[ray_i].wallHitY % TILE_SIZE;
		else
			textureOffsetX = (int)rays[ray_i].wallHitX % TILE_SIZE;

		int	texNum;

		texNum =  rays[ray_i].wallHitContent - 1;
		texture_width = wallTextures[texNum].width;
		texture_height = wallTextures[texNum].height;

		while (y < wallBottomPixel)
		{
			distanceFromTop = y + (wallStripHeight / 2) - (WINDOW_HEIGHT / 2);
			textureOffsetY = distanceFromTop * ((float)texture_height / wallStripHeight);

			// set the color of the wall based on the color from the texture
			texelColor = wallTextures[texNum].texture_buffer[(texture_width * textureOffsetY) + textureOffsetX];
			// texelColor = textures[texNum][(texture_width * textureOffsetY) + textureOffsetX];
			drawPixel(ray_i, y, texelColor);
			// colorBuffer[(WINDOW_WIDTH * y) + ray_i] = texelColor;
			y++;
		}
		while (y < WINDOW_HEIGHT)
		{
			drawPixel(ray_i, y, 0xFF888888);
			y++;
		}

		ray_i++;
	}

}