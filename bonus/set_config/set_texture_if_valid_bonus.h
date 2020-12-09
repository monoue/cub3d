/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture_if_valid.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 12:42:50 by monoue            #+#    #+#             */
/*   Updated: 2020/12/09 15:47:47 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_TEXTURE_IF_VALID_H
# define SET_TEXTURE_IF_VALID_H

# include "../error_exit/error_exit.h"
# include "../global/init_g_ids.h"
# include "../global/init_g_textures.h"
# include "free_str_array.h"

void	set_texture_if_valid(char **element_items);

#endif
