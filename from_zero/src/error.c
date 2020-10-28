/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 15:29:46 by monoue            #+#    #+#             */
/*   Updated: 2020/10/28 12:27:21 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "defs.h"

void	exit_with_error_message(t_error_types message_type,  char *error_content)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	if (message_type == ERRNO)
		perror(NULL);
	else if (message_type == SINGLE)
		ft_putstr_fd(error_content, STDERR_FILENO);
	else if (message_type == ID_OVERLAPPING)
	{
		ft_putstr_fd(".cub file has more than one \"", STDERR_FILENO);
		ft_putstr_fd(error_content, STDERR_FILENO);
		ft_putstr_fd("\" lines.\n", STDERR_FILENO);
	}
	else if (message_type == WRONG_INFO_NUM)
	{
		ft_putstr_fd(".cub file: \"", STDERR_FILENO);
		ft_putstr_fd(error_content, STDERR_FILENO);
		ft_putstr_fd("\" line's informations' number is wrong.\n", STDERR_FILENO);
	}
	else if (message_type == INVALID_INFO)
	{
		ft_putstr_fd(".cub file: \"", STDERR_FILENO);
		ft_putstr_fd(error_content, STDERR_FILENO);
		ft_putstr_fd("\" line's informations is invalid.\n", STDERR_FILENO);
	}
	// TODO: これって、今まだ使っているんだっけ？
	// ERRNO で対応できないかな？
	else if (message_type == INVALID_PATH)
	{
		ft_putstr_fd(".cub file: \"", STDERR_FILENO);
		ft_putstr_fd(error_content, STDERR_FILENO);
		ft_putstr_fd("\" line's path is invalid.\n", STDERR_FILENO);
	}
	else if (message_type == LACKING_ELEMENT)
	{
		ft_putstr_fd(".cub file: \"", STDERR_FILENO);
		ft_putstr_fd(error_content, STDERR_FILENO);
		ft_putstr_fd("\" line is lacking.\n", STDERR_FILENO);
	}
	// TODO: fd の close もここでやる？　だとすれば、fd はグローバル変数？
	exit(EXIT_FAILURE);
}

void	map_exit_failure(char *map_line, char *error_message)
{
	SAFE_FREE(map_line);
	exit_with_error_message(SINGLE, error_message);
}

void	exit_if_too_large_map(char *map_line, size_t height)
{
	const size_t width = ft_strlen(map_line);

	if (height > MAX_MAP_LEN - 1)
		map_exit_failure(map_line, ".cub file: The map is too high.\n");
	if (width > MAX_MAP_LEN)
		map_exit_failure(map_line, ".cub file: The map is too wide.\n");
}

// TODO: そもそも、フリーする必要なくなったらこの関数要らない

// void	exit_freeing_maps()
// {
// 	// SAFE_FREE(g_map);
// 	// SAFE_FREE(g_map_to_check);
// 	exit_with_error_message("SINGLE", "The map is not surrounded by walls.\n");
// }

