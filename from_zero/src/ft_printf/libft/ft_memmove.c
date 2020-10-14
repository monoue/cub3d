/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 14:47:27 by monoue            #+#    #+#             */
/*   Updated: 2020/07/02 11:33:52 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	const char		*s;

	if (src >= dst)
		ft_memcpy(dst, src, len);
	else
	{
		d = dst + (len - 1);
		s = src + (len - 1);
		while (len-- > 0)
			*d-- = *s--;
	}
	return (dst);
}
