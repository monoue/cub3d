/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hook_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:10:31 by monoue            #+#    #+#             */
/*   Updated: 2020/12/10 07:19:11 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_HOOK_BONUS_H
# define EVENT_HOOK_BONUS_H

# include "../defs_bonus.h"
# include "../../minilibx/mlx.h"
# include "../global/init_g_player_bonus.h"
# include "../global/init_g_config_bonus.h"
# include "../global/init_g_rays_bonus.h"
# include "../global/init_g_minimap_flag_bonus.h"
# include "../global/init_g_mlx_bonus.h"

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
