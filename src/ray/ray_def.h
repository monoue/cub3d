/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_def.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 14:27:39 by monoue            #+#    #+#             */
/*   Updated: 2020/11/24 16:36:46 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_DEF_H
# define RAY_DEF_H

# include "coord.h"

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
