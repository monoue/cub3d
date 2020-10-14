/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwaura <miwaura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 15:45:27 by miwaura           #+#    #+#             */
/*   Updated: 2020/07/03 11:48:14 by miwaura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_atoi(const char *str)
{
	long			res;
	unsigned int	i;
	int				pn;

	i = 0;
	pn = 1;
	res = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' ||
		str[i] == '\r' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-')
		pn = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
	{
		if (res > res * 10 + (str[i] - '0'))
			return (pn > 0 ? -1 : 0);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return ((int)res * pn);
}
