/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shape_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 16:13:19 by monoue            #+#    #+#             */
/*   Updated: 2020/12/10 07:19:11 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_SHAPE_BONUS_H
# define DRAW_SHAPE_BONUS_H

# include "../../defs_bonus.h"
# include "../../global/init_g_color_bonus.h"
# include "draw_pixel_bonus.h"

void	draw_rectangle(size_t start_x, size_t start_y, size_t width,
																size_t height);
void	draw_rectangle_minimap(size_t start_x, size_t start_y,
												size_t width, size_t height);
void	draw_line(int x0, int y0, int x1, int y1);
void	draw_line_minimap(int x0, int y0, int x1, int y1);

#endif
