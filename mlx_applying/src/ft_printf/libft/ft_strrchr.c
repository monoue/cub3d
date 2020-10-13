/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 13:50:34 by monoue            #+#    #+#             */
/*   Updated: 2020/08/20 11:18:24 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				len;
	unsigned char	uc;

	uc = (unsigned char)c;
	len = ft_strlen(s);

	// while (len > 0 && s[len] != uc)
	// {
	// 	len--;
	// }
	// if (s[len] == uc)
	// 	return ((char *)(s - len));
	// return (NULL);

	s += len;
	while (len-- > 0 && *s != uc)
		s--;
	if (*s == uc)
		return ((char *)s);
	return (NULL);
}
