/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 11:39:21 by monoue            #+#    #+#             */
/*   Updated: 2020/10/27 12:37:22 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(long num)
{
	if (num < 0)
		return (ft_strjoin_free_both(ft_ctoa('-'), ft_itoa(-num)));
	if (num >= 10)
		return (ft_strjoin_free_both(ft_itoa(num / 10), ft_itoa(num % 10)));
	return (ft_ctoa((char)ITOC(num)));
}
