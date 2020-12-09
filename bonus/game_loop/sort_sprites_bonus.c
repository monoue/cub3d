/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sprites_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 10:33:43 by monoue            #+#    #+#             */
/*   Updated: 2020/12/09 16:45:27 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "update_and_sort_sprites_data_bonus.h"

static void	swap_sprites(size_t index, size_t inner_i)
{
	t_sprite	tmp;

	tmp = g_sprites[index];
	g_sprites[index] = g_sprites[inner_i];
	g_sprites[inner_i] = tmp;
}

static void	sort_sprites_to_bottom(int top_index, int *bot_index)
{
	int	last_swap_index;
	int	index;

	index = top_index;
	last_swap_index = top_index;
	while (index < *bot_index)
	{
		if (g_sprites[index].distance_from_player
			< g_sprites[index + 1].distance_from_player)
		{
			swap_sprites(index, index + 1);
			last_swap_index = index;
		}
		index++;
	}
	*bot_index = last_swap_index;
}

static void	sort_sprites_to_top(int *top_index, int bot_index)
{
	int	last_swap_index;
	int	index;

	last_swap_index = bot_index;
	index = bot_index;
	while (index > *top_index)
	{
		if (g_sprites[index].distance_from_player
			> g_sprites[index - 1].distance_from_player)
		{
			swap_sprites(index, index - 1);
			last_swap_index = index;
		}
		index--;
	}
	*top_index = last_swap_index;
}

void		sort_sprites(void)
{
	int top_index;
	int bot_index;

	top_index = 0;
	bot_index = g_config.sprites_num - 1;
	while (true)
	{
		sort_sprites_to_bottom(top_index, &bot_index);
		if (top_index == bot_index)
			break ;
		sort_sprites_to_top(&top_index, bot_index);
		if (top_index == bot_index)
			break ;
	}
}
