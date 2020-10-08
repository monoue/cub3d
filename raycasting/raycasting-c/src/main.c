#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "defs.h"
#include "graphics.h"
#include "map.h"
#include "player.h"
#include "ray.h"
#include "wall.h"
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
	int	timeToWait;
	float	deltaTime;
	// Compute how long we have until the reach the target frame time in milliseconds
	timeToWait = FRAME_TIME_LENGTH - (SDL_GetTicks() - ticksLastFrame);

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

	deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
	ticksLastFrame = SDL_GetTicks();

	movePlayer(deltaTime);
	castAllRays();
}


void	render()
{
	clearColorBuffer(0xFF000000);

	renderWallProjection();

	// generate3DProjection();

	//	clear the color buffer

	//	display the minimap
	renderMap();
	renderRays();
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
	return (EXIT_SUCCESS);
}