/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_data_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 12:54:41 by monoue            #+#    #+#             */
/*   Updated: 2020/11/30 14:58:28 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line_data_utils.h"

void		exit_if_closing_fd_fails(int fd)
{
	if (close(fd) == ERROR)
		exit_with_error_message(ERRNO, NULL);
}

void		exit_closing_fd(t_error_types message_type, char *error_content,
																		int fd)
{
	exit_if_closing_fd_fails(fd);
	exit_with_error_message(message_type, error_content);
}

/*
** If a render size is of more than four digits, it is taken to be invalid size.
*/

void		get_resolution(const char **infos, int fd)
{
	if (!(g_config.window_width == NOT_SET
									&& g_config.window_height == NOT_SET))
	{
		exit_closing_fd(ID_OVERLAPPING, "R", fd);
	}
	if (ft_count_strs(infos) != 2)
		exit_closing_fd(WRONG_INFO_NUM, "R", fd);
	if (!ft_str_is_numeric(infos[0])
		|| !ft_str_is_numeric(infos[1])
		|| ft_strlen(infos[0]) > 4
		|| ft_strlen(infos[1]) > 4)
	{
		exit_closing_fd(INVALID_INFO, "R", fd);
	}
	mlx_get_screen_size(g_mlx.mlx_ptr, &g_config.window_width,
												&g_config.window_height);
	g_config.window_width = MIN(g_config.window_width,
															ft_atoi(infos[0]));
	g_config.window_height = MIN(g_config.window_height,
															ft_atoi(infos[1]));
	if (g_config.window_width == 0 || g_config.window_height == 0)
		exit_closing_fd(INVALID_INFO, "R", fd);
	g_distance_proj_plane = (g_config.window_width / 2)
														/ tan(FOV_ANGLE / 2);
}

void		exit_if_not_all_elements_are_set(int fd)
{
	size_t	t_i;

	t_i = 0;
	while (t_i < TEXTURES_NUM)
	{
		if (g_textures[t_i].path == NULL)
			exit_closing_fd(LACKING_ELEMENT, g_ids[t_i], fd);
		t_i++;
	}
	if (g_config.window_width == NOT_SET)
		exit_closing_fd(LACKING_ELEMENT, "R", fd);
	if ((int)g_config.floor_color == NOT_SET)
		exit_closing_fd(LACKING_ELEMENT, "F", fd);
	if ((int)g_config.ceiling_color == NOT_SET)
		exit_closing_fd(LACKING_ELEMENT, "C", fd);
}

bool		all_elements_are_set(void)
{
	size_t	t_i;

	t_i = 0;
	while (t_i < TEXTURES_NUM)
	{
		if (g_textures[t_i].path == NULL)
			return (false);
		t_i++;
	}
	if (g_config.window_width == NOT_SET
		|| g_config.window_height == NOT_SET)
	{
		return (false);
	}
	if ((int)g_config.floor_color == NOT_SET
		|| (int)g_config.ceiling_color == NOT_SET)
	{
		return (false);
	}
	return (true);
}
