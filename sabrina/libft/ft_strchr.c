/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 16:03:23 by tauvray           #+#    #+#             */
/*   Updated: 2020/10/12 11:17:54 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int i;

	if (s)
	{
		i = 0;
		while (s[i] != c && s[i] != '\0')
		{
			i++;
		}
		if (s[i] == c)
			return (&(((char *)s)[i]));
		else
			return (NULL);
	}
	return (NULL);
}
