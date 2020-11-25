/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_data_utils.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 12:59:29 by monoue            #+#    #+#             */
/*   Updated: 2020/11/25 12:39:16 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_LINE_DATA_UTILS_H
# define GET_LINE_DATA_UTILS_H

# include "../defs.h"
# include "../error_exit/error_exit.h"
# include "../global/init_g_cubfile_data.h"
# include "../global/init_g_ids.h"
# include "../global/init_g_mlx.h"
# include "../global/init_g_textures.h"
# include "../libft/libft.h"
# include "../../minilibx/mlx.h"

void			get_resolution(const char **infos);
void			exit_if_not_all_elements_are_set(void);
bool			all_elements_are_set(void);

#endif
