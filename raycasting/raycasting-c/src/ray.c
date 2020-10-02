#include "ray.h"

ray_t	rays[NUM_RAYS];

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