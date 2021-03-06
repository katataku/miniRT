/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:15:28 by ahayashi          #+#    #+#             */
/*   Updated: 2022/05/26 20:19:05 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

/*
 * ๐ก = โ(๐ฌโโ๐งโ)/(๐โโ๐งโ)
 *
 * ๅๆฏใ0ใใๅฐใใใจใใฏ่งฃใชใใ
 * โปๅนณ้ขใๅ็นใซใใใจใใใซใกใฉใฎไฝ็ฝฎใใฏใใซใใๅนณ้ขไธใฎไปปๆใฎ็นใฎไฝ็ฝฎใใฏใใซใๅผใใใใฎใ๐ฌโใจใใ
 */
double	calc_t_plane(t_ray *ray, t_plane *plane)
{
	float	denominator;
	float	fraction;
	t_vec3	*s;

	denominator = vec3_inner_product(ray->direction_vec, plane->normal_vec);
	if (denominator == 0)
		return (-1);
	s = vec3_sub(ray->start_vec, plane->point);
	fraction = vec3_inner_product(s, plane->normal_vec);
	free(s);
	return (-fraction / denominator);
}

/*
 * ๆกๆฃๅๅฐๅใ่จ็ฎใใใ
 * cosใฎๅคใใใคใในใซใชใๅ ดๅใฏๅใๅฝใใฃใฆใใชใใจใใฆๆฑใ
 */
double	calc_lambert_cos_plane(t_ray *ray, t_plane *plane, t_light *light)
{
	double	t;
	double	cos;
	t_vec3	*d_vec;
	t_vec3	*p_vec;
	t_vec3	*l_vec;

	t = calc_t_plane(ray, plane);
	d_vec = vec3_multiply(ray->direction_vec, t);
	p_vec = vec3_add(ray->start_vec, d_vec);
	l_vec = vec3_sub(light->point, p_vec);
	cos = cos_of_angles(plane->normal_vec, l_vec);
	free(d_vec);
	free(p_vec);
	free(l_vec);
	if (cos <= 0)
		return (0);
	return (cos);
}
