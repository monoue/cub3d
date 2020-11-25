/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_data_utils.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 12:59:29 by monoue            #+#    #+#             */
/*   Updated: 2020/11/25 09:51:02 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_LINE_DATA_UTILS_H
# define GET_LINE_DATA_UTILS_H

# include "src/defs.h"
# include "src/error_exit/error_exit.h"
# include "src/global/init_g_ids.h"
# include "src/global/init_g_cubfile_data.h"
# include "src/libft/libft.h"

void			get_resolution(const char **infos);
void			exit_if_not_all_elements_are_set(void);
void			set_texture_if_valid(const char **element_items);
bool			all_elements_are_set(void);

#endif
