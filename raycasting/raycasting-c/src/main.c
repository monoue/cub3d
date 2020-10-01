#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include "defs.h"
#include "graphics.h"
#include "map.h"
#include "texture.h"


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
	int		wallHitContent;
}		rays[NUM_RAYS];

bool	isGameRunning = false;
int		ticksLastFrame;

void	setup(void)
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

	// Asks uPNG library to decode all PNG files and loads the wallTextures array
	loadWallTextures();
}


void	movePlayer(float deltaTime)
{
	player.rotationAngle += player.turnDirection * player.turnSpeed * deltaTime;

	const float	moveStep = player.walkDirection * player.walkSpeed * deltaTime;

	// 僕オリジナルの機能（これでバグっているのかも）
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
	// SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	// SDL_Rect	playerRect = {
	// 	player.x * MINIMAP_SCALE_FACTOR,
	// 	player.y * MINIMAP_SCALE_FACTOR,
	// 	player.width * MINIMAP_SCALE_FACTOR,
	// 	player.height * MINIMAP_SCALE_FACTOR
	// };
	// SDL_RenderFillRect(renderer, &playerRect);
	// SDL_RenderDrawLine(
	// 	renderer,
	// 	MINIMAP_SCALE_FACTOR * player.x,
	// 	MINIMAP_SCALE_FACTOR * player.y,
	// 	MINIMAP_SCALE_FACTOR * player.x + cos(player.rotationAngle) * 40,
	// 	MINIMAP_SCALE_FACTOR * player.y + sin(player.rotationAngle) * 40
	// );
}

float	normalizeAngle(float originalAngle)
{
	float	normalAngle;

	normalAngle = remainder(originalAngle, TWO_PI);
	if (normalAngle < 0)
		normalAngle += TWO_PI;
	return (normalAngle);
}

float	distanceBetweenPoints(float x1, float y1, float x2, float y2)
{
	const float	x_diff = x2 - x1;
	const float	y_diff = y2 - y1;

	return (sqrt(pow(x_diff, 2) + pow(y_diff, 2)));
}

void	castRay(float originalRayAngle, int stripId)
{
	float	rayAngle;

	rayAngle = normalizeAngle(originalRayAngle);

	bool	isRayFacingDown = (rayAngle > 0 && rayAngle < PI);
	bool	isRayFacingUp = !isRayFacingDown;
	bool	isRayFacingRight = ((rayAngle < 0.5 * PI) || (rayAngle > 1.5 * PI));
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
	// while (!isOutOfWindow(nextHorzTouchX, nextHorzTouchY))
	while (isInsideMap(nextHorzTouchX, nextHorzTouchY))
	{
		float	xToCheck;
		float	yToCheck;

		xToCheck = nextHorzTouchX;
		yToCheck = nextHorzTouchY;
		if (isRayFacingUp)
			yToCheck = yToCheck - 1;
			// yToCheck--;
		if (mapHasWallAt(xToCheck, yToCheck))
		{
			horzWallHitX = nextHorzTouchX;
			horzWallHitY = nextHorzTouchY;
			horzWallContent = getMapAt((int)floor(yToCheck / TILE_SIZE), (int)floor(xToCheck / TILE_SIZE));
			foundHorzWallHit = true;
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
	// while (!isOutOfWindow(nextVertTouchX, nextVertTouchY))
    while (isInsideMap(nextVertTouchX, nextVertTouchY))
	{
		float	xToCheck;
		float	yToCheck;

		xToCheck = nextVertTouchX;
		yToCheck = nextVertTouchY;
		if (isRayFacingLeft)
			xToCheck = xToCheck - 1;
			// xToCheck--;
		if (mapHasWallAt(xToCheck, yToCheck))
		{
			vertWallHitX = nextVertTouchX;
			vertWallHitY = nextVertTouchY;
			vertWallContent = getMapAt((int)floor(yToCheck / TILE_SIZE), (int)floor(xToCheck / TILE_SIZE));
			foundVertWallHit = true;
			break;
		}
		nextVertTouchX += xstep;
		nextVertTouchY += ystep;
	}
	// const float	horzHitDistance = (foundHorzWallHit)
	float	horzHitDistance = (foundHorzWallHit)
		? distanceBetweenPoints(player.x, player.y, horzWallHitX, horzWallHitY)
		: FLT_MAX;
	// const float	vertHitDistance = (foundVertWallHit)
	float	vertHitDistance = (foundVertWallHit)
		? distanceBetweenPoints(player.x, player.y, vertWallHitX, vertWallHitY)
		: FLT_MAX;
	if (vertHitDistance < horzHitDistance)
	{
		rays[stripId].distance = vertHitDistance;
		rays[stripId].wallHitX = vertWallHitX;
		rays[stripId].wallHitY = vertWallHitY;
		rays[stripId].wallHitContent = vertWallContent;
		rays[stripId].wasHitVertical = true;
	}
	else
	{
		rays[stripId].distance = horzHitDistance;
		rays[stripId].wallHitX = horzWallHitX;
		rays[stripId].wallHitY = horzWallHitY;
		rays[stripId].wallHitContent = horzWallContent;
		rays[stripId].wasHitVertical = false;
	}
	rays[stripId].rayAngle = rayAngle;
}

void	castAllRays(void)
{
	float		rayAngle;
	int			col;

	col = 0;
	while (col < NUM_RAYS)
	{
		// rotationAngle は、向いている真っ正面。
		// col = 0 の時は開始の角度になるようマイナスになり、半分でど真ん中、そして段々とプラスの端っこへ
		rayAngle = player.rotationAngle + atan((col - (NUM_RAYS / 2)) / DIST_PROJ_PLANE);
		castRay(rayAngle, col);
		col++;
	}
}


void	renderRays(void)
{
	// SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	// int	index;

	// index = 0;
	// while (index < NUM_RAYS)
	// {
	// 	SDL_RenderDrawLine(
	// 		renderer,
	// 		MINIMAP_SCALE_FACTOR * player.x,
	// 		MINIMAP_SCALE_FACTOR * player.y,
	// 		MINIMAP_SCALE_FACTOR * rays[index].wallHitX,
	// 		MINIMAP_SCALE_FACTOR * rays[index].wallHitY
	// 	);
	// 	index++;
	// }
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
	// renderPlayer();
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