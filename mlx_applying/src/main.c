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

bool	is_game_running = false;
int		ticks_last_frame;

void	setup(void)
{
	// Asks uPNG library to decode all PNG files and loads the wall_textures array
	load_wall_textures();
}

void	process_input()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT)
			is_game_running = false;
	else if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_ESCAPE)
			is_game_running = false;
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
	int		time_to_wait;
	float	delta_time;
	// Compute how long we have until the reach the target frame time in milliseconds
	time_to_wait = FRAME_TIME_LENGTH - (SDL_GetTicks() - ticks_last_frame);
	// Only delay execution if we are running too fast
	if (time_to_wait > 0 && time_to_wait <= FRAME_TIME_LENGTH)
		SDL_Delay(time_to_wait);
	// これは何のため？
	// と言うのは、(SDL_GetTicks() - ticks_last_frame) == FRAME_TIME_LENGTH(= 1000 / PFS) なのでは？
	// ミリ秒に変換している。
	// ↓
	// つまり、Δtime が経過するごとに、50 * Δtime 分移動している。
	// これが積み重なると、１秒経過するごとに 50 * １ 移動することになる。
	// なので、１秒ごとの移動距離を表している、ということになる。
	delta_time = (SDL_GetTicks() - ticks_last_frame) / 1000.0f;
	ticks_last_frame = SDL_GetTicks();
	move_player(delta_time);
	cast_all_rays();
}

void	render()
{
	clear_color_buffer(0xFF000000);
	render_wall_projection();
	render_map();
	render_rays();
	render_player();
	render_color_buffer();
}

void	release_resources(void)
{
	free_wall_textures();
	destroy_window();
}


int		main(int argc, char **argv)
{
	if (argc < 2)
		return (exit_failure_with_err_msg("You need argument(s).\n"));
	if (ft_strlen(argv[1] < 5) || ft_strncmp(&argv[1][ft_strlen(argv[1] - 4)], ".cub", 4) != 0)
	// if (!ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
		return (exit_failure_with_err_msg(".cub file must be specified.\n"));
	if (argc > 2)
	{
		if (ft_strncmp(argv[2], "--save", ft_strlen(argv[2])) != 0)
			return (exit_failure_with_err_msg("Invalid option. Option: --save\n"));
		save_picture(argv[1]);
	}
	else
		init_game(argv[1]);



































	is_game_running = initialize_window();
	setup();
	while (is_game_running == true)
	{
		process_input();
		update();
		render();
	}
	release_resources();
	return (EXIT_SUCCESS);
}