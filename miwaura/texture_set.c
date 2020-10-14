/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miwaura <miwaura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 13:35:50 by miwaura           #+#    #+#             */
/*   Updated: 2020/09/30 13:35:30 by miwaura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		case_n(t_data *img, char *line, int i, char *ptr)
{
	if (ft_strncmp(line + i, "./textures/redbrick.xpm", 23) == 0)
	{
		n_texture_set(img, ptr, "./textures/redbrick.xpm");
		return (1);
	}
	if (ft_strncmp(line + i, "./textures/greystone.xpm", 24) == 0)
	{
		n_texture_set(img, ptr, "./textures/greystone.xpm");
		return (1);
	}
	return (0);
}

int		get_texture_n(t_data *img, char *line)
{
	int		i;
	char	*ptr;

	img->map.elements_num++;
	i = 3;
	ptr = NULL;
	while (line[i] == ' ')
		i++;
	if (case_n(img, line, i, ptr) == 1)
		return (1);
	if (ft_strncmp(line + i, "./textures/bluestone.xpm", 24) == 0)
	{
		n_texture_set(img, ptr, "./textures/bluestone.xpm");
		return (1);
	}
	if (ft_strncmp(line + i, "./textures/colorstone.xpm", 25) == 0)
	{
		n_texture_set(img, ptr, "./textures/colorstone.xpm");
		return (1);
	}
	return (0);
}

int		case_s(t_data *img, char *line, int i, char *ptr)
{
	if (ft_strncmp(line + i, "./textures/redbrick.xpm", 23) == 0)
	{
		s_texture_set(img, ptr, "./textures/redbrick.xpm");
		return (1);
	}
	else if (ft_strncmp(line + i, "./textures/greystone.xpm", 24) == 0)
	{
		s_texture_set(img, ptr, "./textures/greystone.xpm");
		return (1);
	}
	return (0);
}

int		get_texture_s(t_data *img, char *line)
{
	int		i;
	char	*ptr;

	img->map.elements_num++;
	i = 3;
	ptr = NULL;
	while (line[i] == ' ')
		i++;
	if (case_s(img, line, i, ptr) == 1)
		return (1);
	else if (ft_strncmp(line + i, "./textures/bluestone.xpm", 24) == 0)
	{
		s_texture_set(img, ptr, "./textures/bluestone.xpm");
		return (1);
	}
	else if (ft_strncmp(line + i, "./textures/colorstone.xpm", 25) == 0)
	{
		s_texture_set(img, ptr, "./textures/colorstone.xpm");
		return (1);
	}
	return (0);
}

int		case_w(t_data *img, char *line, int i, char *ptr)
{
	if (ft_strncmp(line + i, "./textures/redbrick.xpm", 23) == 0)
	{
		w_texture_set(img, ptr, "./textures/redbrick.xpm");
		return (1);
	}
	else if (ft_strncmp(line + i, "./textures/greystone.xpm", 24) == 0)
	{
		w_texture_set(img, ptr, "./textures/greystone.xpm");
		return (1);
	}
	return (0);
}
