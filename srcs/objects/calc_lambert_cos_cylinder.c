/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_lambert_cos_cylinder.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 13:58:30 by takkatao          #+#    #+#             */
/*   Updated: 2022/06/04 21:49:19 by takkatao         ###   ########.fr       */
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
	t_vec3	*p_vec;
	enum e_t_type t_type;

	p_vec = calc_p_cylinder(ray, cy);
	h = calc_height(p_vec, cy);
	center = create_p_vec(cy->point, cy->orientation_vec, h);
	t_type = calc_t_type(ray, cy);
	if (t_type == T_T1)
		n_vec = vec3_sub(p_vec, center);
	else
		n_vec = vec3_sub(center, p_vec);
	l_vec = vec3_sub(light->point, p_vec);
	cos = cos_of_angles(n_vec, l_vec);
	free(center);
	free(n_vec);
	free(l_vec);
	free(p_vec);
	if (cos < 0)
		return (0);
	return (cos);
}
