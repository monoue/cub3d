#ifndef COORD_H
# define COORD_H

typedef struct	s_coord {
	float	x;
	float	y;
}				t_coord;

t_coord	*coord_assign(t_coord *dst, float x, float y);
t_coord	*coord_copy(t_coord *dst, t_coord *src);
t_coord	*coord_add(t_coord *dst, t_coord *add);

#endif
