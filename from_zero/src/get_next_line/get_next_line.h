/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 15:05:47 by monoue            #+#    #+#             */
/*   Updated: 2020/07/22 10:40:01 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

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

char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
int		get_next_line(int fd, char **line);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s1);

#endif
