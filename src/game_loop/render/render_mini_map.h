/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_mini_map.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:11:23 by monoue            #+#    #+#             */
/*   Updated: 2020/11/25 10:12:06 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_MINI_MAP_H
# define RENDER_MINI_MAP_H

# include "src/defs.h"
# include "src/global/init_g_player.h"
# include "draw_shape.h"

void	render_mini_map(void);
void	render_player(void);
void	render_lines_to_sprites_center(void);

#endif
