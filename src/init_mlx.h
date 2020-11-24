/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:10:44 by monoue            #+#    #+#             */
/*   Updated: 2020/11/24 09:00:34 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_MLX_H
# define INIT_MLX_H

# include "defs.h"
# include "event_hook.h"
# include "graphics.h"
# include "render_mini_map.h"
# include "player.h"
# include "ray.h"
# include "render_sprites.h" // set_texture_color
# include "render_wall_ray_basis.h" // set_texture_color
# include "save_image.h"
# include "set_color.h"
# include "set_cubfile_data.h"
# include "texture.h"
# include "wall.h"
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
void			init_texture_paths();
bool			map_has_wall_at(float x, float y);

#endif
