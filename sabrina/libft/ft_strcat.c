/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauvray <tauvray@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 16:55:07 by tauvray           #+#    #+#             */
/*   Updated: 2015/02/02 16:44:54 by tauvray          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	int i;
	int fin;

	i = 0;
	fin = ft_strlen(dest);
	while (src[i] != '\0')
	{
		dest[fin + i] = src[i];
		i++;
	}
	dest[fin + i] = '\0';
	return (dest);
}
