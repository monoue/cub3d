/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 15:29:46 by monoue            #+#    #+#             */
/*   Updated: 2020/12/09 16:45:27 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_exit_bonus.h"

static void	err_msg_id_overlapping(char *error_content)
{
	ft_putstr_fd("config file has more than one \"", STDERR_FILENO);
	ft_putstr_fd(error_content, STDERR_FILENO);
	ft_putstr_fd("\" lines\n", STDERR_FILENO);
}

static void	err_msg_wrong_info_num(char *error_content)
{
	ft_putstr_fd("config file: \"", STDERR_FILENO);
	ft_putstr_fd(error_content, STDERR_FILENO);
	ft_putstr_fd("\" line's informations' number is wrong\n",
															STDERR_FILENO);
}

static void	err_msg_invalid_info(char *error_content)
{
	ft_putstr_fd("config file: \"", STDERR_FILENO);
	ft_putstr_fd(error_content, STDERR_FILENO);
	ft_putstr_fd("\" line's informations is invalid\n", STDERR_FILENO);
}

void		exit_with_error_message(t_error_types message_type,
															char *error_content)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	if (message_type == ERRNO)
		perror(NULL);
	else if (message_type == SINGLE)
		ft_putstr_fd(error_content, STDERR_FILENO);
	else if (message_type == ID_OVERLAPPING)
		err_msg_id_overlapping(error_content);
	else if (message_type == WRONG_INFO_NUM)
		err_msg_wrong_info_num(error_content);
	else if (message_type == INVALID_INFO)
		err_msg_invalid_info(error_content);
	else if (message_type == LACKING_ELEMENT)
	{
		ft_putstr_fd("config file: \"", STDERR_FILENO);
		ft_putstr_fd(error_content, STDERR_FILENO);
		ft_putstr_fd("\" line is not above map\n", STDERR_FILENO);
	}
	exit(EXIT_FAILURE);
}
