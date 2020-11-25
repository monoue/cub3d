/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 12:42:52 by monoue            #+#    #+#             */
/*   Updated: 2020/11/25 12:43:21 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "set_texture.h"

void	set_texture(char **texture_path, const char **infos, char *id)
{
	if (*texture_path != NULL)
		exit_with_error_message(ID_OVERLAPPING, id);
	if (ft_count_strs(infos) != 1)
		exit_with_error_message(WRONG_INFO_NUM, id);
	*texture_path = ft_strdup(infos[0]);
}
