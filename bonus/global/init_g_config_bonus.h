/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_g_config_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 12:22:39 by monoue            #+#    #+#             */
/*   Updated: 2020/12/10 07:19:11 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_G_CONFIG_BONUS_H
# define INIT_G_CONFIG_BONUS_H

# include "../defs_bonus.h"

typedef struct	s_config
{
	int			window_width;
	int			window_height;
	t_color		floor_color;
	t_color		ceiling_color;
	size_t		sprites_num;
}				t_config;

extern t_config g_config;

#endif
