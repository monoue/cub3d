/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:11:51 by monoue            #+#    #+#             */
/*   Updated: 2020/11/21 13:11:53 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_COLOR_H
# define SET_COLOR_H

# include "defs.h"
# include "error.h"

void	set_color(t_color *color, const char **infos, char *id);
t_color	create_trgb(int t, int r, int g, int b);

#endif
