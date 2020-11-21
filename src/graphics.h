/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:10:38 by monoue            #+#    #+#             */
/*   Updated: 2020/11/21 13:10:40 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H

# define GRAPHICS_H

# include <stdint.h>
# include <stdbool.h>
# include "defs.h"
# include "init_mlx.h"

// bool	initialize_window(void);
// void	destroy_window(void);
// void	clear_color_buffer(t_color color);
// void	render_color_buffer(void);
void	draw_pixel(int x, int y);
void	draw_rectangle(size_t start_x, size_t start_y, size_t width, size_t height);
void	draw_line(int x0, int y0, int x1, int y1);

extern	t_color g_color;

#endif
