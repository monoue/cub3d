/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_def_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 14:27:39 by monoue            #+#    #+#             */
/*   Updated: 2020/12/10 07:19:11 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_DEF_BONUS_H
# define RAY_DEF_BONUS_H

# include "coord_bonus.h"

typedef struct	s_ray_materials {
	t_coord	*intercept;
	t_coord	*step;
	bool	is_wall_hit_found;
	t_coord	*wall_hit_coord;
	t_coord	*next_touch_coord;
	t_coord	*to_check_coord;
	float	hit_distance;
}				t_ray_materials;

#endif
