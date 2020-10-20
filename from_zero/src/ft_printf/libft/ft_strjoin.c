/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 16:01:19 by monoue            #+#    #+#             */
/*   Updated: 2020/10/20 09:42:30 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	const size_t	s1_len = ft_strlen(s1);
	const size_t	s2_len = ft_strlen(s2);
	size_t			index;
	char			*joined_str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	joined_str = malloc(sizeof(*joined_str) * (s1_len + s2_len + 1));
	if (joined_str == NULL)
		return (NULL);
	index = 0;
	while (index < s1_len)
	{
		joined_str[index] = s1[index];
		index++;
	}
	index = 0;
	while (index < s2_len)
	{
		joined_str[s1_len + index] = s2[index];
		index++;
	}
	joined_str[s1_len + s2_len] = '\0';
	return (joined_str);
}
