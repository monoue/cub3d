/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:11:51 by monoue            #+#    #+#             */
/*   Updated: 2020/11/25 12:36:51 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_COLOR_H
# define SET_COLOR_H

# include "../defs.h"
# include "../error_exit/error_exit.h"
# include "../utils/create_trgb.h"

void	set_color(t_color *color, const char **infos, char *id);

#endif
