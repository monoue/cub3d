/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_data_utils.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 12:59:29 by monoue            #+#    #+#             */
/*   Updated: 2020/12/09 16:54:27 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_LINE_DATA_UTILS_H
# define GET_LINE_DATA_UTILS_H

# include "free_str_array.h"
# include "../defs.h"
# include "../error_exit/error_exit.h"
# include "../global/init_g_config.h"
# include "../global/init_g_distance_proj_plane.h"
# include "../global/init_g_ids.h"
# include "../global/init_g_mlx_bonus.h"
# include "../global/init_g_textures.h"
# include "../../libft/libft.h"
# include "../../minilibx/mlx.h"

void	exit_if_closing_fd_error(int fd);
void	exit_closing_fd(t_error_types message_type, char *error_content,
																	int fd);
void	get_resolution(char **element_items, int fd);
void	exit_if_not_all_elements_are_set(char *config_line, const int fd);
bool	all_elements_are_set(void);

#endif
