/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 12:42:50 by monoue            #+#    #+#             */
/*   Updated: 2020/12/09 10:24:43 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_TEXTURE_H
# define SET_TEXTURE_H

# include "../error_exit/error_exit.h"
# include "free_str_array.h"

void	set_texture(char **texture_path, char **element_items, char *id);

#endif
