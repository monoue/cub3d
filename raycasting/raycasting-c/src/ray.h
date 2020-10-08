#ifndef RAY_H
# define RAY_H

# include <stdbool.h>
# include <limits.h>
# include "defs.h"
# include "graphics.h"
# include "player.h"

typedef struct	s_ray {
	float	rayAngle;
	float	wallHitX;
	float	wallHitY;
	float	distance;
	bool	wasHitVertical;
	int		wallHitContent;
}				t_ray;

extern t_ray	rays[NUM_RAYS];

void	normalizeAngle(float *angle);

float	distanceBetweenPoints(float x1, float y1, float x2, float y2);
void	castRay(float originalRayAngle, int stripId);
void	castAllRays(void);
void	renderRays(void);

#endif