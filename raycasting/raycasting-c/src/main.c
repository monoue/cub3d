#include "constants.h"

const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

// typedef struct	s_player {
// 	float	x;
// 	float	y;
// 	float	width;
// 	float	height;
// 	int		turnDirection;
// 	int		walkDirection;
// 	float	rotationAngle;
// 	float	walkSpeed;
// 	float	turnSpeed;
// }				t_player;

struct	Player {
	float	x;
	float	y;
	float	width;
	float	height;
	int		turnDirection;
	int		walkDirection;
	float	rotationAngle;
	float	walkSpeed;
	float	turnSpeed;
}		player;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
int	isGameRunning = false;
int	ticksLastFrame = 0;

bool	initializeWindow()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == SDL_ERROR)
	{
		ft_putstr_fd("Error initializing SDL.\n", STDERR_FILENO);
		return (false);
	}
	window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS);
	if (window == NULL)
	{
		ft_putstr_fd("Error creating SDL window.\n", STDERR_FILENO);
		return (false);
	}
	renderer = SDL_CreateRenderer(window, DEFAULT_GRAPHIC_DRIVER, 0);
	if (renderer == NULL)
	{
		ft_putstr_fd("Error creating SDL renderer.\n", STDERR_FILENO);
		return (false);
	}
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	return (true);
}

void	destroyWindow()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void	setup()
{
	player.x = WINDOW_WIDTH / 2;
	player.y = WINDOW_HEIGHT / 2;
	player.width = 1;
	player.height = 1;
	player.turnDirection = 0;
	player.walkDirection = 0;
	player.rotationAngle = PI / 2;
	player.walkSpeed = 100;
	player.turnSpeed = 45 * (PI / 180);
	int		walkDirection;
	float	rotationAngle;
	float	walkSpeed;
	float	turnSpeed;
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
bool	isOutOfWindow(const float x, const float y)
{
	return (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT);
}

bool	isSpaceAt(const float pixelX, const float pixelY) {
	if (isOutOfWindow(pixelX, pixelY))
		return (false);
	const int gridX = floor(pixelX / TILE_SIZE);
	const int gridY = floor(pixelY / TILE_SIZE);
	return map[gridY][gridX] == 0 ? true : false;
}

void	movePlayer(float deltaTime)
{
	player.rotationAngle += player.turnDirection * player.turnSpeed * deltaTime;

	const float	moveStep = player.walkDirection * player.walkSpeed * deltaTime;

	const float	moveX = cos(player.rotationAngle) * moveStep;
	const float	moveY = sin(player.rotationAngle) * moveStep;

	float	newPlayerX = player.x;
	float	newPlayerY = player.y;

	if (isSpaceAt(player.x + moveX, player.y))
		newPlayerX += moveX;
	if (isSpaceAt(player.x, player.y + moveY))
		newPlayerY += moveY;

	player.x = newPlayerX;
	player.y = newPlayerY;
}

void	renderPlayer()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_Rect	playerRect = {
		player.x * MINIMAP_SCALE_FACTOR,
		player.y * MINIMAP_SCALE_FACTOR,
		player.width * MINIMAP_SCALE_FACTOR,
		player.height  * MINIMAP_SCALE_FACTOR
	};
	SDL_RenderFillRect(renderer, &playerRect);
	SDL_RenderDrawLine(
		renderer,
		MINIMAP_SCALE_FACTOR * player.x,
		MINIMAP_SCALE_FACTOR * player.y,
		MINIMAP_SCALE_FACTOR * player.x + cos(player.rotationAngle) * 40,
		MINIMAP_SCALE_FACTOR * player.y + sin(player.rotationAngle) * 40
	);
}

void	renderMap()
{
	for (int y = 0; y < MAP_NUM_ROWS; y++)
	{
		for (int x = 0; x < MAP_NUM_COLS; x++)
		{
			const int tileX = x * TILE_SIZE;
			const int tileY = y * TILE_SIZE;
			const int tileColor = map[y][x] == 1 ? EDGE_COLOR : INNER_COLOR;

			SDL_SetRenderDrawColor(renderer, tileColor, tileColor, tileColor, 255);
			SDL_Rect	mapTileRect = {tileX * MINIMAP_SCALE_FACTOR, tileY * MINIMAP_SCALE_FACTOR, TILE_SIZE * MINIMAP_SCALE_FACTOR, TILE_SIZE * MINIMAP_SCALE_FACTOR};
			SDL_RenderFillRect(renderer, &mapTileRect);
		}
	}
}

void	update()
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
}

void	render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	// TODO:
	// Render game objects here.
	renderMap();
	// renderRays();
	renderPlayer();
	SDL_RenderPresent(renderer);
}

int		main()
{
	isGameRunning = initializeWindow();
	setup();
	while (isGameRunning == true)
	{
		processInput();
		update();
		render();
	}
	destroyWindow();
}