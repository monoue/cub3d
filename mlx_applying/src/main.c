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
#include "new.h"

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
	if (event.type == SDL_QUIT)
			isGameRunning = false;
	else if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_ESCAPE)
			isGameRunning = false;
		if (event.key.keysym.sym == SDLK_UP)
			g_player.walk_direction = FRONT;
		if (event.key.keysym.sym == SDLK_DOWN)
			g_player.walk_direction = BACK;
		if (event.key.keysym.sym == SDLK_LEFT)
			g_player.turn_direction = LEFT;
		if (event.key.keysym.sym == SDLK_RIGHT)
			g_player.turn_direction = RIGHT;
	}
	else if (event.type == SDL_KEYUP)
	{
		if (event.key.keysym.sym == SDLK_UP)
			g_player.walk_direction = NEUTRAL;
		if (event.key.keysym.sym == SDLK_DOWN)
			g_player.walk_direction = NEUTRAL;
		if (event.key.keysym.sym == SDLK_LEFT)
			g_player.turn_direction = NEUTRAL;
		if (event.key.keysym.sym == SDLK_RIGHT)
			g_player.turn_direction = NEUTRAL;
	}
}

void	update(void)
{
	int		timeToWait;
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
	move_player(deltaTime);
	castAllRays();
}

void	render()
{
	clear_color_buffer(0xFF000000);
	renderWallProjection();
	renderMap();
	renderRays();
	renderPlayer();
	render_color_buffer();
}

void	releaseResources(void)
{
	freeWallTextures();
	destroy_window();
}


int		main(int argc, char **argv)
{
	if (argc != 2 && argc != 3)
		return (put_err_msg("Invalid arguments.\n"));
	if (!ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
		return (put_err_msg(".cub file must be specified.\n"));
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", ft_strlen(argv[2])) != 0)
			return (put_err_msg("Invalid option. Option: --save\n"));
		save_picture(argv[1]);
	}
	else
		init_game(argv[1]);



































	isGameRunning = initialize_window();
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