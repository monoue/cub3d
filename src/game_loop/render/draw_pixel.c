/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:53:27 by monoue            #+#    #+#             */
/*   Updated: 2020/11/27 09:45:53 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw_pixel.h"

void	draw_pixel(int x, int y)
{
	char	*dst;

	if (x >= g_cubfile_data.window_width || y >= g_cubfile_data.window_height)
		return ;
	dst = &g_img.addr[y * g_img.line_length + x * (g_img.bits_per_pixel / 8)];
	*(unsigned int*)dst = g_color;
}
