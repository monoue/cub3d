/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_with_zero.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 13:18:22 by monoue            #+#    #+#             */
/*   Updated: 2020/10/27 14:22:28 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILL_WITH_ZERO_H
# define FILL_WITH_ZERO_H

# include "../libft.h"
# include "defs.h"

void	fill_output_with_zero(char **str, int margin);
void	fill_empty_with_zero(char **str, int margin, t_format_info *info);

#endif
