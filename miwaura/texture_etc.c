/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_etc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 15:58:23 by miwaura           #+#    #+#             */
/*   Updated: 2020/10/21 09:50:10 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	s_texture_set(t_data *img, char *ptr, char *path)
{
	ptr = img->map.south_texture_path;
	img->map.south_texture_path = ft_strdup(path);
	free(ptr);
}

void	e_texture_set(t_data *img, char *ptr, char *path)
{
	ptr = img->map.east_texture_path;
	img->map.east_texture_path = ft_strdup(path);
	free(ptr);
}

void	n_texture_set(t_data *img, char *ptr, char *path)
{
	ptr = img->map.north_texture_path;
	img->map.north_texture_path = ft_strdup(path);
	free(ptr);
}

void	w_texture_set(t_data *img, char *ptr, char *path)
{
	ptr = img->map.west_texture_path;
	img->map.west_texture_path = ft_strdup(path);
	free(ptr);
}
