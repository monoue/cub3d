/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwaura <miwaura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 14:18:35 by miwaura           #+#    #+#             */
/*   Updated: 2020/07/11 17:38:57 by miwaura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(const char *s1)
{
	void			*s2;
	size_t			len;
	unsigned char	*d;
	unsigned char	*s;

	len = ft_strlen(s1) + 1;
	s2 = malloc(len);
	if (s2 == NULL)
		return (NULL);
	if (s2 == NULL && s1 == NULL)
	{
		return (NULL);
	}
	d = (unsigned char *)s2;
	s = (unsigned char *)s1;
	while (len)
	{
		*d = *s;
		d++;
		s++;
		len--;
	}
	return (s2);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ss;
	int		i;
	int		j;

	ss = (char *)malloc(sizeof(char const) *
	(ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ss)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ss[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		ss[i] = s2[j];
		j++;
		i++;
	}
	ss[i] = '\0';
	return (ss);
}

char	*ft_strchr(const char *s, int c)
{
	int i;

	if ((char)c == '\0')
		return ((char *)s + ft_strlen(s));
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			return (char *)s + i;
		}
		i++;
	}
	return (NULL);
}
