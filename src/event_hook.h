#ifndef EVENT_HOOK_H
# define EVENT_HOOK_H

# include "defs.h"
# include "player.h"
// # include "../minilibx/mlx.h"

/*
** X11 events
*/
# define KEY_PRESS		2
# define KEY_RELEASE	3
# define DESTROY_NOTIFY	17

/*
** X11 masks
*/
# define KEY_PRESS_MASK			1L << 0
# define KEY_RELEASE_MASK		1L << 1
# define STRUCTURE_NOTIFY_MASK	1L << 17

/*
** Mac OS key codes
*/
# define KEY_ESC	53
# define KEY_W		13
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2
# define KEY_LEFT	123
# define KEY_RIGHT	124

int		key_down(int keycode, void *null);
int		key_up(int keycode, void *null);
int		finish_program(void *null);

#endif
