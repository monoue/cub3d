/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture_if_valid_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 12:42:52 by monoue            #+#    #+#             */
/*   Updated: 2020/12/11 09:18:59 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "set_texture_if_valid_bonus.h"

static void	set_texture(char **texture_path, char **element_items, char *id)
{
	if (ft_count_strs((const char **)element_items) != 2)
	{
		free_str_array(element_items);
		exit_with_error_message(WRONG_INFO_NUM, id);
	}
	if (*texture_path != NULL)
	{
		free_str_array(element_items);
		exit_with_error_message(ID_OVERLAPPING, id);
	}
	*texture_path = ft_strdup(element_items[1]);
}

void		set_texture_if_valid(char **element_items)
{
	size_t		t_i;

	t_i = 0;
	while (t_i < TEXTURES_NUM)
	{
		if (ft_strcmp(element_items[0], g_ids[t_i]) == 0)
		{
			set_texture(&g_textures[t_i].path, element_items, g_ids[t_i]);
			break ;
		}
		t_i++;
	}
	free_str_array(element_items);
	if (t_i == TEXTURES_NUM)
		exit_with_error_message(SINGLE, INVALID_INDICATOR);
}
