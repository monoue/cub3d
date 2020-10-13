#include "ray.h"

t_ray	rays[NUM_RAYS];

void	normalizeAngle(float *angle)
{
	*angle = remainder(*angle, TWO_PI);
	if (*angle < 0)
		*angle += TWO_PI;
}

float	distanceBetweenPoints(float x1, float y1, float x2, float y2)
{
	const float	x_diff = x2 - x1;
	const float	y_diff = y2 - y1;

	return (sqrt(pow(x_diff, 2) + pow(y_diff, 2)));
}

void	castRay(float rayAngle, int stripId)
{
	normalizeAngle(&rayAngle);

	bool	isRayFacingDown = (rayAngle > 0 && rayAngle < PI);
	bool	isRayFacingUp = !isRayFacingDown;
	bool	isRayFacingRight = ((rayAngle < 0.5 * PI) || (rayAngle > 1.5 * PI));
	bool	isRayFacingLeft = !isRayFacingRight;
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
	yintercept = floor(g_player.y / TILE_SIZE) * TILE_SIZE;
	if (isRayFacingDown)
		yintercept += TILE_SIZE;

	// Find the x-coordinate of the closest horizontal grid intersection
	xintercept = g_player.x + (yintercept - g_player.y) / tan(rayAngle);

	// Calculate the increment xstep and y step
	ystep = isRayFacingDown ? TILE_SIZE : -(TILE_SIZE);

	xstep = TILE_SIZE / tan(rayAngle);
	if ((isRayFacingLeft && xstep > 0) || (isRayFacingRight && xstep < 0))
		xstep *= -1;
	float	nextHorzTouchX = xintercept;
	float	nextHorzTouchY = yintercept;
	// increment xstep and ystep until we find a wall
	while (isInsideMap(nextHorzTouchX, nextHorzTouchY))
	{
		float	xToCheck;
		float	yToCheck;

		xToCheck = nextHorzTouchX;
		yToCheck = nextHorzTouchY;
		if (isRayFacingUp)
			yToCheck--;
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
	}
	// ///////////////////////////////////////////
	// // VERTICAL RAY-GRID INTERSECTION CODE //
	// ///////////////////////////////////////////
	bool	foundVertWallHit = false;
	float	vertWallHitX = 0;
	float	vertWallHitY = 0;
	int		vertWallContent = 0;

	// Find the x-coordinate of the closest vertical grid intersection
	xintercept = floor(g_player.x / TILE_SIZE) * TILE_SIZE;
	if (isRayFacingRight)
		xintercept += TILE_SIZE;
	// Find the y-coordinate of the closest vertical grid intersection
	yintercept = g_player.y + (xintercept - g_player.x) * tan(rayAngle);
	// Calculate the increment xstep and y step
	xstep = isRayFacingRight ? TILE_SIZE : -(TILE_SIZE);

	ystep = TILE_SIZE * tan(rayAngle);
	if ((isRayFacingDown && ystep < 0) || (isRayFacingUp && ystep > 0))
		ystep *= -1;

	float	nextVertTouchX = xintercept;
	float	nextVertTouchY = yintercept;

	// increment xstep and ystep until we find a wall
    while (isInsideMap(nextVertTouchX, nextVertTouchY))
	{
		float	xToCheck;
		float	yToCheck;

		xToCheck = nextVertTouchX;
		yToCheck = nextVertTouchY;
		if (isRayFacingLeft)
			xToCheck--;
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
		? distanceBetweenPoints(g_player.x, g_player.y, horzWallHitX, horzWallHitY)
		: FLT_MAX;
	// const float	vertHitDistance = (foundVertWallHit)
	float	vertHitDistance = (foundVertWallHit)
		? distanceBetweenPoints(g_player.x, g_player.y, vertWallHitX, vertWallHitY)
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
		rayAngle = g_player.rotation_angle + atan((col - (NUM_RAYS / 2)) / DIST_PROJ_PLANE);
		castRay(rayAngle, col);
		col++;
	}
}


void	renderRays(void)
{
	int	index;

	index = 0;
	while (index < NUM_RAYS)
	{
		drawLine
		(
			g_player.x * MINIMAP_SCALE_FACTOR,
			g_player.y * MINIMAP_SCALE_FACTOR,
			rays[index].wallHitX * MINIMAP_SCALE_FACTOR,
			rays[index].wallHitY * MINIMAP_SCALE_FACTOR,
			0xFF0000FF
		);
		index++;
	}
}