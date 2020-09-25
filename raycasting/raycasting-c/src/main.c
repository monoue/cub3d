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

struct	Ray {
	float	rayAngle;
	float	wallHitX;
	float	wallHitY;
	float	distance;
	bool	wasHitVertical;
	bool	isRayFacingUp;
	bool	isRayFacingDown;
	bool	isRayFacingLeft;
	bool	isRayFacingRight;
	int		wallHitContent;
}		rays[NUM_RAYS];

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

float	distanceBetweenPoints(float x1, float y1, float x2, float y2)
{
	const float	x_diff = x2 - x1;
	const float	y_diff = y2 - y1;

	return (sqrt(pow(x_diff, 2) + pow(y_diff, 2)));
}

bool	isSpaceAt(const float pixelX, const float pixelY) {
	if (isOutOfWindow(pixelX, pixelY))
		return (false);
	const int gridX = floor(pixelX / TILE_SIZE);
	const int gridY = floor(pixelY / TILE_SIZE);
	return map[gridY][gridX] == 0 ? true : false;
}

bool	mapHasWallAt(const float pixelX, const float pixelY) {
	if (isOutOfWindow(pixelX, pixelY))
		return (true);
	const int gridX = floor(pixelX / TILE_SIZE);
	const int gridY = floor(pixelY / TILE_SIZE);
	return map[gridY][gridX] != 0 ? true : false;
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

float	normalizeAngle(float originalAngle)
{
	float	normalAngle;

	normalAngle = originalAngle;
	while (normalAngle < 0)
		normalAngle += TWO_PI;
	normalAngle = remainder(normalAngle, TWO_PI);
	return (normalAngle);
}

void	castRay(float originalRayAngle, int stripId)
{
	float	rayAngle;

	rayAngle = normalizeAngle(originalRayAngle);

	bool	isRayFacingDown = (rayAngle > 0 && rayAngle < PI);
	bool	isRayFacingUp = !isRayFacingDown;
	bool	isRayFacingRight = ((rayAngle < PI / 2.0) || (rayAngle > PI * (3 / 2)));
	bool	isRayFacingLeft = !isRayFacingRight;

	// TODO: All that crazy logic for horz, vert, ...
	// ...
	float	xintercept;
	float	yintercept;

	float	xstep;
	float	ystep;

	// ///////////////////////////////////////////
	// // HORIZONTAL RAY-GRID INTERSECTION CODE //
	// ///////////////////////////////////////////
	bool	foundHorzWallHit = false;
	float	horzWallHitX = 0;
	float	horzWallHitY = 0;
	int		horzWallContent = 0;

	// Find the y-coordinate of the closest horizontal grid intersection
	yintercept = floor(player.y / TILE_SIZE) * TILE_SIZE;
	if (isRayFacingDown)
		yintercept += TILE_SIZE;

	// Find the x-coordinate of the closest horizontal grid intersection
	xintercept = player.x + (yintercept - player.y) / tan(rayAngle);

	// Calculate the increment xstep and y step
	ystep = isRayFacingDown ? TILE_SIZE : -(TILE_SIZE);

	xstep = TILE_SIZE / tan(rayAngle);
	if ((isRayFacingLeft && xstep > 0) || (isRayFacingRight && xstep < 0))
		xstep *= -1;

	float	nextHorzTouchX = xintercept;
	float	nextHorzTouchY = yintercept;

	// increment xstep and ystep until we find a wall
	while (!isOutOfWindow(nextHorzTouchX, nextHorzTouchY))
	{
		float	xToCheck;
		float	yToCheck;

		xToCheck = nextHorzTouchX;
		yToCheck = nextHorzTouchY;
		if (isRayFacingUp)
			yToCheck--;
		if (mapHasWallAt(xToCheck, yToCheck))
		{
			foundHorzWallHit = true;
			horzWallHitX = nextHorzTouchX;
			horzWallHitY = nextHorzTouchY;
			horzWallContent = map[(int)floor(horzWallHitY)][(int)floor(horzWallHitX)];
			break;
		}
		nextHorzTouchX += xstep;
		nextHorzTouchY += ystep;

		// Calculate both horizontal and vertical hit distances and choose the smallest one
	}

	// ///////////////////////////////////////////
	// // VERTICAL RAY-GRID INTERSECTION CODE //
	// ///////////////////////////////////////////
	bool	foundVertWallHit = false;
	float	vertWallHitX = 0;
	float	vertWallHitY = 0;
	int		vertWallContent = 0;

	// Find the x-coordinate of the closest vertical grid intersection
	xintercept = floor(player.x / TILE_SIZE) * TILE_SIZE;
	if (isRayFacingRight)
		xintercept += TILE_SIZE;

	// Find the y-coordinate of the closest vertical grid intersection
	yintercept = player.y + (xintercept - player.x) * tan(rayAngle);

	// Calculate the increment xstep and y step
	xstep = isRayFacingRight ? TILE_SIZE : -(TILE_SIZE);

	ystep = TILE_SIZE * tan(rayAngle);
	if ((isRayFacingDown && ystep < 0) || (isRayFacingUp && ystep > 0))
		ystep *= -1;

	float	nextVertTouchX = xintercept;
	float	nextVertTouchY = yintercept;

	// increment xstep and ystep until we find a wall
	while (!isOutOfWindow(nextHorzTouchX, nextHorzTouchY))
	{
		float	xToCheck;
		float	yToCheck;

		xToCheck = nextVertTouchX;
		yToCheck = nextVertTouchY;
		if (isRayFacingLeft)
			xToCheck--;
		if (mapHasWallAt(xToCheck, yToCheck))
		{
			foundVertWallHit = true;
			vertWallHitX = nextVertTouchX;
			vertWallHitY = nextVertTouchY;
			vertWallContent = map[(int)floor(vertWallHitY)][(int)floor(vertWallHitX)];
			break;
		}
		nextVertTouchX += xstep;
		nextVertTouchY += ystep;
	}
	const float	horzHitDistance = (foundHorzWallHit)
		? distanceBetweenPoints(player.x, player.y, horzWallHitX, horzWallHitY)
		: MAXFLOAT;
	const float	vertHitDistance = (foundVertWallHit)
		? distanceBetweenPoints(player.x, player.y, vertWallHitX, vertWallHitY)
		: MAXFLOAT;
	if (vertHitDistance < horzHitDistance)
	{
		rays[stripId].wallHitX = vertWallHitX;
		rays[stripId].wallHitY = vertWallHitY;
		rays[stripId].distance = vertHitDistance;
		rays[stripId].wasHitVertical = true;
		rays[stripId].wallHitContent = vertWallContent;
	}
	else
	{
		rays[stripId].wallHitX = horzWallHitX;
		rays[stripId].wallHitY = horzWallHitY;
		rays[stripId].distance = horzHitDistance;
		rays[stripId].wasHitVertical = false;
		rays[stripId].wallHitContent = horzWallContent;
	}
	rays[stripId].rayAngle = rayAngle;
	rays[stripId].isRayFacingDown = isRayFacingDown;
	rays[stripId].isRayFacingUp = isRayFacingUp;
	rays[stripId].isRayFacingRight = isRayFacingRight;
	rays[stripId].isRayFacingLeft = isRayFacingLeft;
}

void	castAllRays()
{
	// start the first ray subtracting the half of our FOV
	float	rayAngle = player.rotationAngle - (FOV_ANGLE / 2);

	int		stripId;

	stripId = 0;
	while (stripId < NUM_RAYS)
	{
		castRay(rayAngle, stripId);

		rayAngle += (FOV_ANGLE / NUM_RAYS);
		stripId++;
	}
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

void	renderRays()
{
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	int	index;

	index = 0;
	while (index < NUM_RAYS)
	{
		SDL_RenderDrawLine(
			renderer,
			MINIMAP_SCALE_FACTOR * player.x,
			MINIMAP_SCALE_FACTOR * player.y,
			MINIMAP_SCALE_FACTOR * rays[index].wallHitX,
			MINIMAP_SCALE_FACTOR * rays[index].wallHitY
		);
		index++;
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
	castAllRays();
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