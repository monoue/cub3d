/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_data_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 12:54:41 by monoue            #+#    #+#             */
/*   Updated: 2020/11/25 13:02:23 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line_data_utils.h"

/*
** If a render size is of more than four digits, it is taken to be invalid size.
*/

void		get_resolution(const char **infos)
{
	if (!(g_cubfile_data.window_width == NOT_SET
									&& g_cubfile_data.window_height == NOT_SET))
	{
		exit_with_error_message(ID_OVERLAPPING, "R");
	}
	if (ft_count_strs(infos) != 2)
		exit_with_error_message(WRONG_INFO_NUM, "R");
	if (!ft_str_is_numeric(infos[0])
		|| !ft_str_is_numeric(infos[1])
		|| ft_strlen(infos[0]) > 4
		|| ft_strlen(infos[1]) > 4)
	{
		exit_with_error_message(INVALID_INFO, "R");
	}
	mlx_get_screen_size(g_mlx.mlx_ptr, &g_cubfile_data.window_width,
												&g_cubfile_data.window_height);
	g_cubfile_data.window_width = MIN(g_cubfile_data.window_width,
															ft_atoi(infos[0]));
	g_cubfile_data.window_height = MIN(g_cubfile_data.window_height,
															ft_atoi(infos[1]));
	if (g_cubfile_data.window_width < 200 || g_cubfile_data.window_height < 200)
		exit_with_error_message(SINGLE, SIZE_NOT_ENOUGH);
	if (g_cubfile_data.window_width == 0 || g_cubfile_data.window_height == 0)
		exit_with_error_message(INVALID_INFO, "R");
}

void		exit_if_not_all_elements_are_set(void)
{
	size_t	t_i;

	t_i = 0;
	while (t_i < TEXTURES_NUM)
	{
		if (g_textures[t_i].path == NULL)
			exit_with_error_message(LACKING_ELEMENT, g_ids[t_i]);
		t_i++;
	}
	if (g_cubfile_data.window_width == NOT_SET)
		exit_with_error_message(LACKING_ELEMENT, "R");
	if ((int)g_cubfile_data.floor_color == NOT_SET)
		exit_with_error_message(LACKING_ELEMENT, "F");
	if ((int)g_cubfile_data.ceiling_color == NOT_SET)
		exit_with_error_message(LACKING_ELEMENT, "C");
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
	if (g_cubfile_data.window_width == NOT_SET
		|| g_cubfile_data.window_height == NOT_SET)
	{
		return (false);
	}
	if ((int)g_cubfile_data.floor_color == NOT_SET
		|| (int)g_cubfile_data.ceiling_color == NOT_SET)
	{
		return (false);
	}
	return (true);
}
