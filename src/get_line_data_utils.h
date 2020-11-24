/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_data_utils.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 12:59:29 by monoue            #+#    #+#             */
/*   Updated: 2020/11/24 12:59:30 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_LINE_DATA_UTILS_H
# define GET_LINE_DATA_UTILS_H

# include "defs.h"
# include "graphics.h"

typedef struct	s_cubfile_data
{
	int			window_width;
	int			window_height;
	t_color		floor_color;
	t_color		ceiling_color;
	size_t		sprites_num;
}				t_cubfile_data;

extern t_cubfile_data g_cubfile_data;

void			get_resolution(const char **infos);
void			exit_if_not_all_elements_are_set(void);
void			set_texture_if_valid(const char **element_items);
bool			all_elements_are_set(void);

#endif
