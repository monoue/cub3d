/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:11:51 by monoue            #+#    #+#             */
/*   Updated: 2020/11/25 09:18:09 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_COLOR_H
# define SET_COLOR_H

# include "src/defs.h"
# include "src/error_exit/error_exit.h"

void	set_color(t_color *color, const char **infos, char *id);

#endif
