/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_str_array_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 07:31:54 by monoue            #+#    #+#             */
/*   Updated: 2020/12/09 16:45:27 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free_str_array_bonus.h"

void	free_str_array(char **arr)
{
	size_t	index;

	index = 0;
	while (arr[index] != NULL)
	{
		SAFE_FREE(arr[index]);
		index++;
	}
	SAFE_FREE(arr);
}
