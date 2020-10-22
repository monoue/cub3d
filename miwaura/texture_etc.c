/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_etc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 15:58:23 by miwaura           #+#    #+#             */
/*   Updated: 2020/10/14 13:40:46 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	s_texture_set(t_data *img, char *ptr, char *path)
{
	ptr = img->map.s_tex_path;
	img->map.s_tex_path = ft_strdup(path);
	free(ptr);
}

void	e_texture_set(t_data *img, char *ptr, char *path)
{
	ptr = img->map.e_tex_path;
	img->map.e_tex_path = ft_strdup(path);
	free(ptr);
}

void	n_texture_set(t_data *img, char *ptr, char *path)
{
	ptr = img->map.n_tex_path;
	img->map.n_tex_path = ft_strdup(path);
	free(ptr);
}

void	w_texture_set(t_data *img, char *ptr, char *path)
{
	ptr = img->map.w_tex_path;
	img->map.w_tex_path = ft_strdup(path);
	free(ptr);
}
