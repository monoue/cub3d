/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:10:18 by monoue            #+#    #+#             */
/*   Updated: 2020/11/21 13:33:25 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFS_H
# define DEFS_H

# include <math.h>
# include <stdint.h>

# include "./libft/libft.h"

# define SUCCESS				0
# define HALF_PI				1.57079633
# define TWO_PI					6.28318530
# define PI						3.14159265
# define TWO_PI					6.28318530
# define TILE_SIZE				512
# define MAX_MAP_LEN			50
# define MINIMAP_SCALE_FACTOR	0.035
# define IMGDIR					"./images"
# define FOV_ANGLE				1.04719755
# define NUM_RAYS				300
# define MAX_WINDOW_WIDTH		3840
# define MAX_SPRITES_NUM		2500

# define WALL_C '1'
# define SPRITE_C '2'
# define FPS 30

# define TO_LEFT -1
# define TO_RIGHT 1

typedef uint32_t	t_color;

typedef enum	e_move_directions
{
	NEUTRAL,
	RIGHT,
	BACK,
	LEFT,
	FRONT,

	WALK_DIRECTIONS_NUM
}				t_move_directions;

typedef enum	e_textures_num
{
	NORTH,
	EAST,
	WEST,
	SOUTH,
	SPRITE,

	TEXTURES_NUM
}				t_textures_num;

typedef enum	e_error_types
{
	ERRNO,
	SINGLE,
	ID_OVERLAPPING,
	WRONG_INFO_NUM,
	INVALID_INFO,
	LACKING_ELEMENT,

	ERROR_TYPES_NUM
}				t_error_types;

# define SUCCESS 0
# define NEUTRAL 0

#endif
