/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 16:06:06 by monoue            #+#    #+#             */
/*   Updated: 2020/08/17 08:31:53 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	bool			minus_flag;
	unsigned int	i;
	long			n;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	minus_flag = false;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			minus_flag = true;
		i++;
	}
	n = 0;
	while (ft_isdigit(str[i]))
	{
		n = n * 10 + (str[i] - '0');
		i++;
	}
	return (minus_flag ? (int)-n : (int)n);
}
