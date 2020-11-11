#ifndef RAY_H
# define RAY_H

# include <stdbool.h>
# include <limits.h>
# include "defs.h"
# include "graphics.h"
# include "set_cubfile_data.h"
# include "check_map_error.h"
# include "init_mlx.h"
# include "player.h"
# include "float.h"

# include "test.h"

typedef struct	s_coord {
	float	x;
	float	y;
}				t_coord;

typedef struct	s_ray {
	float		ray_angle;
	t_coord		wall_hit;
	float		distance;
	bool		was_hit_vertical;
	char		wall_hit_content;
	t_textures	direction;
}				t_ray;

typedef struct	s_ray_materials {
	t_coord	*intercept;
	t_coord	*step;
	bool	is_wall_hit_found;
	t_coord	*wall_hit;
	char	wall_content;
	t_coord	*next_touch;
	t_coord	*to_check;
	float	hit_distance;
}				t_ray_materials;

extern t_ray	rays[MAX_WINDOW_WIDTH];

void	normalize_angle(float *angle);

// char	get_map_at(size_t y, size_t x);
float	distance_between_points(float x1, float y1, float x2, float y2);
void	cast_ray(float original_ray_angle, size_t strip_id);
void	cast_all_rays(void);
void	render_rays(void);

#endif
