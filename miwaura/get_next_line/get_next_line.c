/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwaura <miwaura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 15:29:31 by miwaura           #+#    #+#             */
/*   Updated: 2020/08/06 16:01:34 by miwaura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*join_mod(char *save_buf, char **line, int flag)
{
	char	*ptr;
	char	*tmp_line;
	char	*new_s;

	ptr = NULL;
	if ((ptr = ft_strchr(save_buf, '\n')))
	{
		*ptr = '\0';
		ptr++;
	}
	tmp_line = *line;
	*line = ft_strjoin(*line, save_buf);
	free(tmp_line);
	if (ptr)
	{
		new_s = ft_strdup(ptr);
	}
	else
	{
		new_s = ptr;
	}
	if (flag)
		free(save_buf);
	return (new_s);
}

int			get_next_line(int fd, char **line)
{
	static char		*save[MAX_FD + 1];
	char			*buf;
	int				rv;

	if (!(*line = ft_strdup("")))
		return (-1);
	if (!(buf = (char *)malloc(sizeof(char) * (100 + 1))))
		return (-1);
	if (save[fd])
		save[fd] = join_mod(save[fd], line, 1);
	while (!save[fd] && (rv = read(fd, buf, 100)))
	{
		if (rv == -1 || !*line)
		{
			free(buf);
			return (-1);
		}
		buf[rv] = '\0';
		save[fd] = join_mod(buf, line, 0);
	}
	free(buf);
	if (rv != 0 || save[fd])
		return (1);
	else
		return (0);
}
