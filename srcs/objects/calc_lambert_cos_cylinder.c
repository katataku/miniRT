/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_lambert_cos_cylinder.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 13:58:30 by takkatao          #+#    #+#             */
/*   Updated: 2022/05/31 13:59:27 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

double	calc_lambert_cos_cylinder(t_ray *ray, t_cylinder *cy, t_light *light)
{
	double	cos;
	double	h;
	t_vec3	*center;
	t_vec3	*n_vec;
	t_vec3	*l_vec;

	h = calc_height(ray->p_vec, cy);
	center = create_p_vec(cy->point, cy->orientation_vec, h);
	if (ray->t_type == T_T1)
		n_vec = vec3_sub(ray->p_vec, center);
	else
		n_vec = vec3_sub(center, ray->p_vec);
	l_vec = vec3_sub(light->point, ray->p_vec);
	cos = cos_of_angles(n_vec, l_vec);
	free(center);
	if (cos < 0)
		return (0);
	return (cos);
}
