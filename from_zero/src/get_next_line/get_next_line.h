/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 15:05:47 by monoue            #+#    #+#             */
/*   Updated: 2020/10/15 13:05:53 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "../ft_printf/libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <time.h>
# include <stdio.h>
# include <fcntl.h>

# define MAX_FD		256
# define NOT_EOF	1
# define FILE_END	0
# define ERROR		-1
# define NOT_FOUND	-1
# define SAFE_FREE(ptr) {free(ptr);ptr = NULL;}
# define BUFFER_SIZE	1024

int		get_next_line(int fd, char **line);

#endif
