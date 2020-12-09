/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_ray_facing.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monoue <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 16:36:34 by monoue            #+#    #+#             */
/*   Updated: 2020/11/25 11:18:53 by monoue           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_RAY_FACING_H
# define IS_RAY_FACING_H

# include "../../defs.h"
# include "stdbool.h"

bool is_ray_facing_down(float angle);
bool is_ray_facing_up(float angle);
bool is_ray_facing_right(float angle);
bool is_ray_facing_left(float angle);

#endif
