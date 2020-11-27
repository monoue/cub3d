/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_g_cubfile_data.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 13:08:19 by monoue            #+#    #+#             */
/*   Updated: 2020/11/25 13:08:20 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_G_CUBFILE_DATA_H
# define INIT_G_CUBFILE_DATA_H

# include "../defs.h"

typedef struct	s_cubfile_data
{
	int			window_width;
	int			window_height;
	t_color		floor_color;
	t_color		ceiling_color;
	size_t		sprites_num;
}				t_cubfile_data;

extern t_cubfile_data g_cubfile_data;

#endif