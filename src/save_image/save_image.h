/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_image.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:11:41 by monoue            #+#    #+#             */
/*   Updated: 2020/11/27 08:28:45 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAVE_IMAGE_H
# define SAVE_IMAGE_H

# include "../defs.h"
# include "../global/init_g_img.h"
# include "../set_cubfile_data/set_cubfile_data.h"
# include "write_image.h"

# define FILE_HEADER_SIZE 14
# define INFO_HEADER_SIZE 40
# define HEADER_SIZE (FILE_HEADER_SIZE + INFO_HEADER_SIZE)

# define FILE_TYPE_1_OFFSET	0
# define FILE_TYPE_2_OFFSET	1
# define FILE_SIZE_OFFSET	2
# define RESERVED_1_OFFSET		6
# define RESERVED_2_OFFSET		8
# define OFFSET_TO_PIXEL_DATA_OFFSET	10
# define INFO_HEADER_SIZE_OFFSET 14
# define IMAGE_WIDTH_OFFSET	18
# define IMAGE_HEIGHT_OFFSET	22
# define PLANES_OFFSET			26
# define BITS_PER_PIXEL_OFFSET	28
# define COMPRESSION_METHOD_OFFSET	30
# define IMAGE_SIZE_OFFSET		34
# define HORZ_RESOLUTION_OFFSET	38
# define VERT_RESOLUTION_OFFSET	42
# define TOTAL_COLORS_OFFSET		46
# define IMPORTANT_COLORS_OFFSET	50

# define PLANES			1

void	save_image();

#endif
