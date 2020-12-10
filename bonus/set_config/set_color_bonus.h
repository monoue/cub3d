/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:11:51 by monoue            #+#    #+#             */
/*   Updated: 2020/12/10 07:19:11 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_COLOR_BONUS_H
# define SET_COLOR_BONUS_H

# include "../defs_bonus.h"
# include "../error_exit/error_exit_bonus.h"
# include "../utils/create_trgb_bonus.h"
# include "free_str_array_bonus.h"

void	set_color(t_color *color, char **element_items, char *id);

#endif
