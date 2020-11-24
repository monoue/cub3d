/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:10:44 by monoue            #+#    #+#             */
/*   Updated: 2020/11/24 16:52:06 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_MLX_H
# define INIT_MLX_H

# include "draw_shape.h"
# include "event_hook.h"
# include "player.h"
# include "cast_all_rays_to_wall.h"
# include "render/render_background.h"
# include "render/render_mini_map.h"
# include "render/render_wall_ray_basis.h"
# include "render/render_sprites.h"
# include "set_color.h"
# include "sprite.h"
# include "../minilibx/mlx.h"

typedef struct	s_img
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct	s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_mlx;

extern	t_mlx g_mlx;
extern	t_img g_img;

void			mlx(void);
bool			map_has_wall_at(float x, float y);

#endif
