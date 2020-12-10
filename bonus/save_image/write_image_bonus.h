/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_image_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:18:48 by monoue            #+#    #+#             */
/*   Updated: 2020/12/10 07:19:11 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRITE_IMAGE_BONUS_H
# define WRITE_IMAGE_BONUS_H

# include <unistd.h>

# include "../global/init_g_config_bonus.h"
# include "../global/init_g_img_bonus.h"
# include "../../libft/libft.h"

void	write_image(int fd, const unsigned int image_size);

#endif
