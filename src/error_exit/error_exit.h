/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:10:26 by monoue            #+#    #+#             */
/*   Updated: 2020/12/11 09:18:20 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_EXIT_H
# define ERROR_EXIT_H

# include "../../libft/libft.h"
# include "../defs.h"
# include <errno.h>

# define CONFIG "config file: "
# define INVALID_FILE_PATH CONFIG"Texture file's path is invalid\n"
# define SEVERAL_SPAWN_POINTS CONFIG"The map has several spawn points\n"
# define MAP_HAS_EMPTY_LINES "config file: The map has empty lines\n"
# define MAP_NOT_CLOSED "config file: The player is not surrounded by walls\n"
# define MAP_WRONG_PLACE "config file: The map is in the wrong place\n"
# define PLAYER_NOT_IN_MAP "config file: The map does not have the player\n"
# define NO_MAP "config file: The map is not set\n"
# define NO_ARG "No arguments\n"
# define MAP_TOO_HIGH "config file: The map is too high\n"
# define MAP_TOO_WIDE "config file: The map is too wide\n"
# define MAP_INVALID "config file: The map includes invalid information\n"
# define INVALID_INDICATOR "config file: Invalid type indicator\n"

void	exit_with_error_message(t_error_types message_type,
														char *error_content);
void	exit_if_closing_fd_error(int fd);
void	map_exit_failure(char *map_line, char *error_message, int fd);
void	exit_if_too_large_map(char *map_line, size_t height, int fd);

#endif
