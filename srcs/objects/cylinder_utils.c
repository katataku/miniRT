/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 13:56:27 by takkatao          #+#    #+#             */
/*   Updated: 2022/06/04 22:13:34 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

double	calc_height(t_vec3 *p_vec, t_cylinder	*cylinder)
{
	double	h;
	double	cos;
	t_vec3	*hypotenuse_vec;

	hypotenuse_vec = vec3_sub(p_vec, cylinder->point);
	cos = vec3_inner_product(hypotenuse_vec, cylinder->orientation_vec) \
			/ vec3_norm(hypotenuse_vec);
	h = sqrt(pow(vec3_norm(hypotenuse_vec), 2) - pow(cylinder->radius, 2));
	free(hypotenuse_vec);
	if (cos > 0)
		return (h);
	else
		return (-h);
}

t_vec3	*create_p_vec(t_vec3 *s, t_vec3 *d, double t)
{
	t_vec3	*p_vec;
	t_vec3	*d_vec;

	d_vec = vec3_multiply(d, t);
	p_vec = vec3_add(s, d_vec);
	free(d_vec);
	return (p_vec);
}

double	decide_t(double t1, double t2, t_ray *ray, t_cylinder *cylinder)
{
	t_vec3	*p_vec;
	double	height;

	p_vec = create_p_vec(ray->start_vec, ray->direction_vec, t1);
	height = calc_height(p_vec, cylinder);
	free(p_vec);
	if (height >= 0 && height <= cylinder->height)
	{
		return (t1);
	}
	p_vec = create_p_vec(ray->start_vec, ray->direction_vec, t2);
	height = calc_height(p_vec, cylinder);
	free(p_vec);
	if (height >= 0 && height <= cylinder->height)
	{
		return (t2);
	}
	return (-1);
}

enum e_t_type	decide_t_type(double t1, double t2, t_ray *ray, t_cylinder *cy)
{
	t_vec3	*p_vec;
	double	height;

	p_vec = create_p_vec(ray->start_vec, ray->direction_vec, t1);
	height = calc_height(p_vec, cy);
	free(p_vec);
	if (height >= 0 && height <= cy->height)
	{
		return (T_T1);
	}
	p_vec = create_p_vec(ray->start_vec, ray->direction_vec, t2);
	height = calc_height(p_vec, cy);
	free(p_vec);
	if (height >= 0 && height <= cy->height)
	{
		return (T_T2);
	}
	return (T_NOT_CROSS);
}

t_vec3	*calc_p_cylinder(t_ray *ray, t_cylinder	*cylinder)
{
	double	t;

	t = calc_t_cylinder(ray, cylinder);
	return (create_p_vec(ray->start_vec, ray->direction_vec, t));
}
