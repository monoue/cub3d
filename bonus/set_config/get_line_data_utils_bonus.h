/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_data_utils_bonus.h                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 12:59:29 by monoue            #+#    #+#             */
/*   Updated: 2020/12/10 07:19:11 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_LINE_DATA_UTILS_BONUS_H
# define GET_LINE_DATA_UTILS_BONUS_H

# include "free_str_array_bonus.h"
# include "../defs_bonus.h"
# include "../error_exit/error_exit_bonus.h"
# include "../global/init_g_config_bonus.h"
# include "../global/init_g_distance_proj_plane_bonus.h"
# include "../global/init_g_ids_bonus.h"
# include "../global/init_g_mlx_bonus.h"
# include "../global/init_g_textures_bonus.h"
# include "../../libft/libft.h"
# include "../../minilibx/mlx.h"

void	exit_if_closing_fd_error(int fd);
void	exit_closing_fd(t_error_types message_type, char *error_content,
																	int fd);
void	get_resolution(char **element_items, int fd);
void	exit_if_not_all_elements_are_set(char *config_line, const int fd);
bool	all_elements_are_set(void);

#endif
