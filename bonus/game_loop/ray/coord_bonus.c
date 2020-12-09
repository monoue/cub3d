/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 12:51:07 by monoue            #+#    #+#             */
/*   Updated: 2020/12/09 16:45:36 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "coord_bonus.h"

t_coord	*coord_assign(t_coord *dst, float x, float y)
{
	dst->x = x;
	dst->y = y;
	return (dst);
}

t_coord	*coord_copy(t_coord *dst, t_coord *src)
{
	coord_assign(dst, src->x, src->y);
	return (dst);
}

t_coord	*coord_add(t_coord *dst, t_coord *add)
{
	coord_assign(dst, dst->x + add->x, dst->y + add->y);
	return (dst);
}
