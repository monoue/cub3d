/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 17:11:03 by monoue            #+#    #+#             */
/*   Updated: 2020/07/23 12:27:46 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	hlen;
	size_t	nlen;
	size_t	i;
	size_t	j;

	hlen = ft_strlen(haystack);
	nlen = ft_strlen(needle);
	if (*needle == '\0')
		return ((char *)haystack);
	if (nlen > hlen)
		return (NULL);
	i = 0;
	while (i + nlen <= hlen)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && needle[j] != '\0')
			j++;
		if (needle[j] == '\0')
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
