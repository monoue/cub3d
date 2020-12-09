/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_data_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 12:54:41 by monoue            #+#    #+#             */
/*   Updated: 2020/12/09 16:45:27 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line_data_utils_bonus.h"

void		exit_closing_fd(t_error_types message_type, char *error_content,
																		int fd)
{
	exit_if_closing_fd_error(fd);
	exit_with_error_message(message_type, error_content);
}

void		exit_closing_fd_freeing_str(t_error_types message_type,
										char *error_content, int fd, char *str)
{
	SAFE_FREE(str);
	exit_closing_fd(message_type, error_content, fd);
}

void		exit_closing_fd_freeing_str_array(t_error_types message_type,
										char *error_content, int fd, char **arr)
{
	free_str_array(arr);
	exit_closing_fd(message_type, error_content, fd);
}

/*
** If a render size is of more than four digits, it is taken to be invalid size.
*/

void		get_resolution(char **element_items, int fd)
{
	if (!(g_config.window_width == NOT_SET
									&& g_config.window_height == NOT_SET))
	{
		exit_closing_fd_freeing_str_array(ID_OVERLAPPING, "R", fd,
																element_items);
	}
	if (ft_count_strs((const char **)element_items) != 3)
		exit_closing_fd(WRONG_INFO_NUM, "R", fd);
	if (!ft_str_is_numeric(element_items[1])
		|| !ft_str_is_numeric(element_items[2])
		|| ft_strlen(element_items[1]) > 4
		|| ft_strlen(element_items[2]) > 4)
		exit_closing_fd_freeing_str_array(INVALID_INFO, "R", fd, element_items);
	mlx_get_screen_size(g_mlx.mlx_ptr, &g_config.window_width,
												&g_config.window_height);
	g_config.window_width = MIN(g_config.window_width,
													ft_atoi(element_items[1]));
	g_config.window_height = MIN(g_config.window_height,
													ft_atoi(element_items[2]));
	if (g_config.window_width == 0 || g_config.window_height == 0)
		exit_closing_fd_freeing_str_array(INVALID_INFO, "R", fd, element_items);
	g_distance_proj_plane = (g_config.window_width / 2)
														/ tan(FOV_ANGLE / 2);
	free_str_array(element_items);
}

void		exit_if_not_all_elements_are_set(char *config_line, const int fd)
{
	size_t	t_i;

	t_i = 0;
	while (t_i < TEXTURES_NUM)
	{
		if (g_textures[t_i].path == NULL)
			exit_closing_fd_freeing_str(LACKING_ELEMENT, g_ids[t_i], fd,
																config_line);
		t_i++;
	}
	if (g_config.window_width == NOT_SET)
		exit_closing_fd_freeing_str(LACKING_ELEMENT, "R", fd, config_line);
	if ((int)g_config.floor_color == NOT_SET)
		exit_closing_fd_freeing_str(LACKING_ELEMENT, "F", fd, config_line);
	if ((int)g_config.ceiling_color == NOT_SET)
		exit_closing_fd_freeing_str(LACKING_ELEMENT, "C", fd, config_line);
}
