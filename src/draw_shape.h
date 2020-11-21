/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shape.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 16:13:19 by monoue            #+#    #+#             */
/*   Updated: 2020/11/21 16:17:37 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_SHAPE_H
# define DRAW_SHAPE_H

# include "defs.h"
# include "graphics.h"

void	draw_rectangle(size_t start_x, size_t start_y, size_t width,
																size_t height);
void	draw_rectangle_minimap(size_t start_x, size_t start_y,
												size_t width, size_t height);
void	draw_line(int x0, int y0, int x1, int y1);
void	draw_line_minimap(int x0, int y0, int x1, int y1);

#endif
