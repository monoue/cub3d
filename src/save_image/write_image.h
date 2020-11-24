/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_image.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:18:48 by monoue            #+#    #+#             */
/*   Updated: 2020/11/24 13:18:49 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRITE_IMAGE_H
# define WRITE_IMAGE_H

# include "unistd.h"
# include "get_line_data_utils.h"

void	write_image(int fd, const unsigned int image_size);

#endif
