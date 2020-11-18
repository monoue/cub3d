#ifndef RAY_H
# define RAY_H

# include <stdbool.h>
# include <limits.h>
# include "coord.h"
# include "defs.h"
# include "graphics.h"
# include "init_mlx.h"
# include "map_check.h"
# include "map_error.h"
# include "player.h"
# include "set_cubfile_data.h"
# include <float.h>

# include "test.h"

typedef struct	s_ray_to_wall {
	float		ray_angle;
	t_coord		*wall_hit_coord;
	float		distance;
	bool		was_hit_vertical;
	t_textures_num	wall_hit_direction;
}				t_ray_to_wall;

typedef struct	s_ray_to_sprite {
	float		ray_angle;
	t_coord		*wall_hit_coord;
	float		distance;
	bool		was_hit_vertical;
	// char		wall_hit_content;
	t_textures_num	direction;
}				t_ray_to_sprite;

typedef struct	s_ray_materials {
	t_coord	*intercept;
	t_coord	*step;
	bool	is_wall_hit_found;
	t_coord	*wall_hit_coord;
	// char	wall_content;
	t_coord	*next_touch_coord;
	t_coord	*to_check_coord;
	float	hit_distance;
}				t_ray_materials;

extern t_ray_to_wall	g_rays[MAX_WINDOW_WIDTH];

void	normalize_angle(float *angle);

char	get_map_at(t_coord *coord);
float	distance_between_points(float x1, float y1, float x2, float y2);
void	cast_ray_to_wall(float original_ray_angle, size_t strip_id);
// void	cast_all_rays(void);
void	render_rays(void);
void	cast_all_rays_to_wall(void);

#endif
