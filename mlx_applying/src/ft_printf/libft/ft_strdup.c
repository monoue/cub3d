/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 15:32:49 by monoue            #+#    #+#             */
/*   Updated: 2020/08/20 10:27:22 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *original_s)
{
	char	*duplicated_s;
	size_t	index;

	if (!original_s)
		return (NULL);
	duplicated_s = malloc(ft_strlen(original_s) + 1);
	if (duplicated_s == NULL)
		return (NULL);
	index = 0;
	while (original_s[index] != '\0')
	{
		duplicated_s[index] = original_s[index];
		index++;
	}
	duplicated_s[index] = '\0';
	return (duplicated_s);
}
