#ifndef RAY_H
# define RAY_H

# include <stdbool.h>
# include <limits.h>
# include "defs.h"
# include "graphics.h"
# include "player.h"

typedef struct	s_ray {
	float	ray_angle;
	float	wall_hit_x;
	float	wall_hit_y;
	float	distance;
	bool	was_hit_vertical;
	int		wall_hit_content;
}				t_ray;

extern t_ray	rays[NUM_RAYS];

void	normalize_angle(float *angle);

float	distance_between_points(float x1, float y1, float x2, float y2);
void	cast_ray(float original_ray_angle, int strip_id);
void	cast_all_rays(void);
void	render_rays(void);

#endif