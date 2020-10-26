/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_etc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 12:50:21 by miwaura           #+#    #+#             */
/*   Updated: 2020/10/26 14:36:13 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_sprites_positions(t_data *img)
{
	int i;
	int j;
	int cnt;

	i = 0;
	cnt = 0;
	while (img->w_map[i])
	{
		j = 0;
		while (img->w_map[i][j])
		{
			if (img->w_map[i][j] == '2')
			{
				img->sprite[cnt].x = j;
				img->sprite[cnt].y = i;
				cnt++;
			}
			j++;
		}
		i++;
	}
}

void	sprites_draw(t_data *img, int *utils)
{
	char	*dst;

	utils[5] = img->sprite_cal.dw_start_y;
	while (utils[5] < img->sprite_cal.dw_end_y)
	{
		utils[2] = (utils[5] - img->sprite_cal.vmscreen) * 256\
		- img->map.window_height * 128 + img->sprite_cal.sprite_h * 128;
		utils[3] = ((utils[2] * TEX_HEIGHT) / img->sprite_cal.sprite_h) / 256;
		dst = img->tex[8].addr + (utils[3] * img->tex[8].line_length\
		+ utils[1] * (img->tex[8].b_per_pix / 8));
		utils[0] = *(unsigned int *)dst;
		if (0x00000000 != utils[0])
			my_mlx_pixel_put(img, utils[4], utils[5], utils[0]);
		utils[5]++;
	}
}

void	sprites(t_data *img, int x)
{
	int		utils[6];

	while (x < img->sprite_num)
	{
		sprite_calculation(img, x);
		utils[4] = img->sprite_cal.dw_start_x;
		while (utils[4] < img->sprite_cal.dw_end_x)
		{
			utils[1] = (int)(256 * (utils[4] - (-img->sprite_cal.sprite_w /\
			2 + img->sprite_cal.screen_x)) * TEX_WIDTH /\
			img->sprite_cal.sprite_w) / 256;
			if (img->sprite_cal.trans_y > 0 && utils[4] > 0 && utils[4] <\
			img->map.window_width && img->sprite_cal.trans_y <\
			img->zbuffer[utils[4]])
			{
				sprites_draw(img, utils);
			}
			utils[4]++;
		}
		x++;
	}
}

int		get_sprite(t_data *img, char *line)
{
	int		i;
	char	*ptr;

	img->map.elements_num++;
	i = 2;
	while (line[i] == ' ')
		i++;
	if (ft_strncmp(line + i, "./textures/barrel.xpm", 21) == 0)
	{
		ptr = img->map.sprite_tex_path;
		img->map.sprite_tex_path = ft_strdup("./textures/barrel.xpm");
		free(ptr);
		return (1);
	}
	return (0);
}
