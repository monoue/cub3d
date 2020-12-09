/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:12:14 by monoue            #+#    #+#             */
/*   Updated: 2020/12/09 15:39:39 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "set_color.h"

static bool		is_out_of_color_range(int trgb_element)
{
	return (trgb_element < 0 || trgb_element > 255);
}

static size_t	count_specific_c(const char *str, char c)
{
	size_t	index;
	size_t	c_count;

	c_count = 0;
	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] == c)
			c_count++;
		index++;
	}
	return (c_count);
}

/*
** If a color size is of more than three digits, it is taken to be invalid.
*/

static void		exit_with_error_message_freeing_str_arrays(int message_type,
char *error_content, char **str1, char **str2)
{
	free_str_array(str1);
	free_str_array(str2);
	exit_with_error_message(message_type, error_content);
}

static void		exit_if_color_line_is_invalid(t_color color,
								char **element_items, char **num_strs, char *id)
{
	size_t	index;

	if ((int)color != NOT_SET)
		exit_with_error_message_freeing_str_arrays(ID_OVERLAPPING, id,
													element_items, num_strs);
	if (ft_count_strs((const char **)element_items) != 2)
		exit_with_error_message_freeing_str_arrays(WRONG_INFO_NUM, id,
													element_items, num_strs);
	if (count_specific_c(element_items[1], ',') != 2
		|| ft_count_strs((const char **)num_strs) != 3)
		exit_with_error_message_freeing_str_arrays(INVALID_INFO, id,
													element_items, num_strs);
	index = 0;
	while (index < 3)
	{
		if (!ft_str_is_numeric(num_strs[index])
				|| ft_strlen(num_strs[index]) > 3)
			exit_with_error_message_freeing_str_arrays(INVALID_INFO, id,
													element_items, num_strs);
		index++;
	}
}

void			set_color(t_color *color, char **element_items, char *id)
{
	size_t	rgb_index;
	int		rgb_elements[3];
	char	**num_strs;

	num_strs = NULL;
	num_strs = ft_split(element_items[1], ',');
	exit_if_color_line_is_invalid(*color, element_items, num_strs, id);
	free_str_array(element_items);
	rgb_index = 0;
	while (rgb_index < 3)
	{
		rgb_elements[rgb_index] = ft_atoi(num_strs[rgb_index]);
		if (is_out_of_color_range(rgb_elements[rgb_index]))
		{
			free_str_array(num_strs);
			exit_with_error_message(INVALID_INFO, id);
		}
		rgb_index++;
	}
	free_str_array(num_strs);
	*color = create_trgb(
		0,
		rgb_elements[0],
		rgb_elements[1],
		rgb_elements[2]);
}
