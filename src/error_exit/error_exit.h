/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:10:26 by monoue            #+#    #+#             */
/*   Updated: 2020/11/27 09:53:22 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_EXIT_H
# define ERROR_EXIT_H

# include "../libft/libft.h"
# include "../defs.h"
# include <errno.h>

# define INVALID_FILE_PATH "Texture file's path is invalid.\n"
# define SEVERAL_SPAWN_POINTS "The map has several spawn points.\n"
# define MAP_HAS_EMPTY_LINES ".cub file: The map has empty lines.\n"
# define MAP_NOT_CLOSED "The map is not surrounded by walls.\n"
# define MAP_WRONG_PLACE "The map is in the wrong place.\n"

void	map_exit_failure(char *map_line, char *error_message);
void	exit_with_error_message(t_error_types message_type,
														char *error_content);

#endif
