/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hook.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:10:31 by monoue            #+#    #+#             */
/*   Updated: 2020/12/01 14:32:32 by monoue           ###   ########.fr       */
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

/*
** Mac OS key codes
*/
# define KEY_ESC	53
# define KEY_W		13
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2
# define KEY_M		46
# define KEY_LEFT	123
# define KEY_RIGHT	124

void		event_hook(void);

#endif
