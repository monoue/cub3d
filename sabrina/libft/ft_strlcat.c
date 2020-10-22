/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauvray <tauvray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 18:24:27 by tauvray           #+#    #+#             */
/*   Updated: 2015/03/21 12:16:24 by tauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	unsigned int i;
	unsigned int len_dst;
	unsigned int len_src;

	len_dst = 0;
	len_src = 0;
	i = 0;
	if (dst && src)
	{
		len_dst = ft_strlen(dst);
		len_src = ft_strlen(src);
		if (size < len_dst)
			return (size + len_src);
		while (src[i] != '\0' && (len_dst + i + 1) < size)
		{
			dst[len_dst + i] = src[i];
			i++;
		}
		dst[len_dst + i] = '\0';
	}
	return (len_dst + len_src);
}
