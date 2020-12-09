/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hook.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:10:31 by monoue            #+#    #+#             */
/*   Updated: 2020/12/08 08:04:07 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_HOOK_H
# define EVENT_HOOK_H

# include "../defs.h"
# include "../../minilibx/mlx.h"
# include "../global/init_g_player.h"
# include "../global/init_g_config.h"
# include "../global/init_g_rays.h"
# include "../global/init_g_minimap_flag.h"
# include "../global/init_g_mlx.h"

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

# if defined(__APPLE__)

/*
** Mac OS key codes
*/
#  define KEY_ESC	53
#  define KEY_W		13
#  define KEY_A		0
#  define KEY_S		1
#  define KEY_D		2
#  define KEY_M		46
#  define KEY_LEFT	123
#  define KEY_RIGHT	124

# else

/*
** for Virtual Machine
*/
#  define KEY_ESC	0xff1b
#  define KEY_W		0x0077
#  define KEY_A		0x0061
#  define KEY_S		0x0073
#  define KEY_M		0x006d
#  define KEY_D		0x0064
#  define KEY_LEFT	0xff51
#  define KEY_RIGHT	0xff53

# endif

void		event_hook(void);

#endif
