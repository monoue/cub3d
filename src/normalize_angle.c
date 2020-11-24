/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_angle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 14:42:56 by monoue            #+#    #+#             */
/*   Updated: 2020/11/24 14:43:30 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "normalize_angle.h"

void	normalize_angle(float *angle)
{
	*angle = remainder(*angle, TWO_PI);
	if (*angle < 0)
		*angle += TWO_PI;
}
