/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 13:56:27 by takkatao          #+#    #+#             */
/*   Updated: 2022/05/31 14:00:21 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

double	calc_height(t_vec3 *p_vec, t_cylinder	*cylinder)
{
	double	h;
	t_vec3	*hypotenuse_vec;

	hypotenuse_vec = vec3_sub(p_vec, cylinder->point);
	h = sqrt(pow(vec3_norm(hypotenuse_vec), 2) - pow(cylinder->radius, 2));
	free(hypotenuse_vec);
	return (h);
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
