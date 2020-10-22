/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/09 16:53:31 by sperrin           #+#    #+#             */
/*   Updated: 2020/10/22 16:48:55 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_slablen(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == '2'
		|| line[i] == ' ')
			count++;
		else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W')
			count++;
		else if (line[i] == 'E')
			count++;
		i++;
	}
	return (count);
}

char	*ft_slab(t_env *e, char *line, int *i, int j)
{
	char	*slab;

	if (!(slab = malloc(sizeof(char) * (ft_slablen(line) + 1))))
		put_error("ERROR\nMALLOC FAILLED DUDE\n");
	while (line[*i] != '\0')
	{
		if (line[*i] == ' ')
			line[*i] = '0';
		if ((line[*i] == '0' || line[*i] == '1' || line[*i] == 'N')
			|| (line[*i] == 'E' || line[*i] == 'S' || line[*i] == 'W'))
			slab[j++] = line[*i];
		else if (line[*i] == '2')
		{
			slab[j++] = line[*i];
			e->p.spr++;
		}
		else if (line[*i] != ' ')
		{
			free(slab);
			return (NULL);
		}
		(*i)++;
	}
	slab[j] = '\0';
	return (slab);
}

int		ft_map(t_env *e, char *line, int *i)
{
	char	**tmp;
	int		j;
	char	s;

	e->check = 1;
	if (!(tmp = malloc(sizeof(char *) * (e->p.mapy + 2))))
		put_error("ERROR\nMALLOC FAILLED DUDE\n");
	j = -1;
	while (++j < e->p.mapy)
		tmp[j] = e->map[j];
	if ((tmp[e->p.mapy] = ft_slab(e, line, i, 0)) == NULL)
	{
		free(tmp);
		put_error("ERROR\nINVALID MAP DUDE\n");
	}
	tmp[e->p.mapy + 1] = NULL;
	if (e->p.mapy > 0)
		free(e->map);
	e->map = tmp;
	e->p.mapy++;
	if ((e->p.mapx = ft_slablen(line)) == -1)
		put_error("ERROR\nINVALID MAP DUDE\n");
	if (e->p.mapy > 1 && (s = ft_strchr(line, '0') == NULL))
		e->check = 0;
	return (1);
}
