/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_if_closing_fd_error.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 08:21:03 by monoue            #+#    #+#             */
/*   Updated: 2020/12/09 08:21:26 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_exit.h"

void	exit_if_closing_fd_error(int fd)
{
	if (close(fd) == ERROR)
		exit_with_error_message(ERRNO, NULL);
}
