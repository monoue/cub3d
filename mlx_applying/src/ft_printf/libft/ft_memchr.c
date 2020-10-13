/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 13:22:57 by monoue            #+#    #+#             */
/*   Updated: 2020/07/02 11:38:31 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*s1;

	s1 = s;
	while (n-- > 0)
	{
		if (*s1 == (char)c)
			return ((void *)s1);
		s1++;
	}
	return (NULL);
}
