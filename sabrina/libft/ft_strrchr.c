/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sperrin <sperrin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 16:39:05 by tauvray           #+#    #+#             */
/*   Updated: 2020/10/12 11:15:48 by sperrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int lenght;

	lenght = ft_strlen((char *)s);
	while (s[lenght] != c && lenght != 0)
	{
		lenght--;
	}
	if (s[lenght] == c)
		return (&(((char *)s)[lenght]));
	else
		return (NULL);
}
