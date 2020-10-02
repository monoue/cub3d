#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include "defs.h"
#include "graphics.h"
#include "map.h"
#include "player.h"
#include "ray.h"
#include "texture.h"

bool	isGameRunning = false;
int		ticksLastFrame;

void	setup(void)
{
	// Asks uPNG library to decode all PNG files and loads the wallTextures array
	loadWallTextures();
}


void	processInput()
{
	SDL_Event event;

	SDL_PollEvent(&event);
	switch (event.type)
	{
		case SDL_QUIT:
			isGameRunning = false;
			break ;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
				isGameRunning = false;

			if (event.key.keysym.sym == SDLK_UP)
				player.walkDirection = FRONT;
			if (event.key.keysym.sym == SDLK_DOWN)
				player.walkDirection = BACK;
			if (event.key.keysym.sym == SDLK_LEFT)
				player.turnDirection = LEFT;
			if (event.key.keysym.sym == SDLK_RIGHT)
				player.turnDirection = RIGHT;
			break ;
		case SDL_KEYUP:

			if (event.key.keysym.sym == SDLK_UP)
				player.walkDirection = NEUTRAL;
			if (event.key.keysym.sym == SDLK_DOWN)
				player.walkDirection = NEUTRAL;
			if (event.key.keysym.sym == SDLK_LEFT)
				player.turnDirection = NEUTRAL;
			if (event.key.keysym.sym == SDLK_RIGHT)
				player.turnDirection = NEUTRAL;
			break ;
	}
}

void	update(void)
{
	// Compute how long we have until the reach the target frame time in milliseconds
	int	timeToWait = FRAME_TIME_LENGTH - (SDL_GetTicks() - ticksLastFrame);

	// Only delay execution if we are running too fast
	if (timeToWait > 0 && timeToWait <= FRAME_TIME_LENGTH)
		SDL_Delay(timeToWait);
	// これは何のため？
	// と言うのは、(SDL_GetTicks() - ticksLastFrame) == FRAME_TIME_LENGTH(= 1000 / PFS) なのでは？
	// ミリ秒に変換している。
	// ↓
	// つまり、Δtime が経過するごとに、50 * Δtime 分移動している。
	// これが積み重なると、１秒経過するごとに 50 * １ 移動することになる。
	// なので、１秒ごとの移動距離を表している、ということになる。
	float	deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
	ticksLastFrame = SDL_GetTicks();

	movePlayer(deltaTime);
	castAllRays();
}

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

void	render()
{
	clearColorBuffer(0xFF000000);

	renderWallProjection();

	// generate3DProjection();

	//	clear the color buffer

	//	display the minimap
	renderMap();
	// renderRays();
	renderPlayer();
	renderColorBuffer();

}

void	releaseResources(void)
{
	freeWallTextures();
	destroyWindow();
}

int		main(int argc, char **argv)
{
	isGameRunning = initializeWindow();
	setup();
	while (isGameRunning == true)
	{
		processInput();
		update();
		render();
	}
	releaseResources();
}