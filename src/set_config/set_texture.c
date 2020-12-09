/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 12:42:52 by monoue            #+#    #+#             */
/*   Updated: 2020/12/09 10:44:22 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "set_texture.h"

void	set_texture(char **texture_path, char **element_items, char *id)
{
	if (ft_count_strs((const char **)element_items) != 2)
	{
		// free_str_array(element_items);
		exit_with_error_message(WRONG_INFO_NUM, id);
	}
	if (*texture_path != NULL)
	{
		free_str_array(element_items);
		exit_with_error_message(ID_OVERLAPPING, id);
	}
	*texture_path = ft_strdup(element_items[1]);
	// ft_strcpy(*texture_path, element_items[1]);
	// *texture_path = element_items[1];
	// free_str_array(element_items);
	// SAFE_FREE(element_items);
}
