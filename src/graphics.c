/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:53:27 by monoue            #+#    #+#             */
/*   Updated: 2020/11/21 16:16:39 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

t_color	g_color;

void	draw_pixel(int x, int y)
{
	char	*dst;

	dst = &g_img.addr[y * g_img.line_length + x * (g_img.bits_per_pixel / 8)];
	*(unsigned int*)dst = g_color;
}

