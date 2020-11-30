/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_image.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:18:48 by monoue            #+#    #+#             */
/*   Updated: 2020/11/30 12:37:51 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRITE_IMAGE_H
# define WRITE_IMAGE_H

# include "unistd.h"
# include "../global/init_g_config.h"
# include "../global/init_g_img.h"
# include "../libft/libft.h"

void	write_image(int fd, const unsigned int image_size);

#endif
