/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_g_textures.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 09:53:36 by monoue            #+#    #+#             */
/*   Updated: 2020/12/01 12:20:50 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_G_TEXTURES_H
# define INIT_G_TEXTURES_H

# include "../defs.h"

typedef struct	s_texture
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	char	*path;
}				t_texture;

extern			t_texture g_textures[TEXTURES_NUM];

void			init_texture_paths(void);

#endif
