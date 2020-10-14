/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 15:05:56 by monoue            #+#    #+#             */
/*   Updated: 2020/07/21 13:49:32 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		ft_min(int n1, int n2)
{
	if (n1 <= n2)
		return (n1);
	return (n2);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*str != '\0')
	{
		str++;
		len++;
	}
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	int		i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	p = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(*p));
	if (p == NULL)
		return (NULL);
	i = 0;
	while (*s1 != '\0')
		p[i++] = *s1++;
	while (*s2 != '\0')
		p[i++] = *s2++;
	p[i] = '\0';
	return (p);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	i;

	s2 = malloc(sizeof(*s2) * (ft_strlen(s1) + 1));
	if (s2 == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	srclen;
	size_t	minlen;
	size_t	i;

	if (s == NULL)
		return (NULL);
	srclen = ft_strlen(s);
	if (start > srclen)
		return (ft_strdup(""));
	minlen = ft_min(srclen - start, len);
	p = malloc((minlen + 1) * sizeof(*p));
	if (p == NULL)
		return (NULL);
	s += start;
	i = 0;
	while (minlen-- > 0)
		p[i++] = *s++;
	p[i] = '\0';
	return (p);
}
