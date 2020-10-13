/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 16:23:14 by monoue            #+#    #+#             */
/*   Updated: 2020/07/02 11:38:22 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long	n2;
	long	d;

	n2 = (long)n;
	d = 1;
	if (n2 < 0)
	{
		ft_putchar_fd('-', fd);
		n2 *= -1;
	}
	while (n2 >= 10 * d)
		d *= 10;
	while (d)
	{
		ft_putchar_fd(ft_itoc(n2 / d), fd);
		n2 %= d;
		d /= 10;
	}
}
