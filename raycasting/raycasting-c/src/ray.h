#ifndef RAY_H
# define RAY_H

# include <stdbool.h>
# include <limits.h>
# include "defs.h"
# include "graphics.h"
# include "player.h"

typedef struct	ray_s {
	float	rayAngle;
	float	wallHitX;
	float	wallHitY;
	float	distance;
	bool	wasHitVertical;
	int		wallHitContent;
}				ray_t;

extern ray_t	rays[NUM_RAYS];

float	normalizeAngle(float originalAngle);

float	distanceBetweenPoints(float x1, float y1, float x2, float y2);
void	castRay(float originalRayAngle, int stripId);
void	castAllRays(void);
void	renderRays(void);

#endif