/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:30:16 by ahayashi          #+#    #+#             */
/*   Updated: 2022/05/27 13:54:37 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

double	calc_lambert_cos_sphere(t_ray *ray, t_sphere *sphere, t_light *light)
{
	double	cos;
	t_vec3	*d_vec;
	t_vec3	*p_vec;
	t_vec3	*n_vec;
	t_vec3	*l_vec;

	d_vec = vec3_multiply(ray->direction_vec, calc_t_sphere(ray, sphere));
	p_vec = vec3_add(ray->start_vec, d_vec);
	n_vec = vec3_sub(p_vec, sphere->center);
	l_vec = vec3_sub(light->point, p_vec);
	cos = cos_of_angles(n_vec, l_vec);
	free(d_vec);
	free(p_vec);
	free(n_vec);
	free(l_vec);
	if (cos <= 0)
		return (0);
	return (cos);
}

/*
 * ๐ก =(โ๐ตยฑโ(๐ต^2โ4๐ด๐ถ))/2๐ด
 *
 * ๐ด = |๐โ|^2
 * ๐ต = 2(๐ฌโโ๐โ)
 * ๐ถ = |๐ฌโ|^2โ๐^2
 * โป็ใๅ็นใซใใใจใใ็ใฎไธญๅฟใๅ็นใซ้ใชใใใใซๅนณ่ก็งปๅใใฆใใใใฐ่ฏใใฎใง
 * ใซใกใฉใฎไฝ็ฝฎใใฏใใซใใ็ใฎไธญๅฟใฎไฝ็ฝฎใใฏใใซใๅผใใใใฎใ๐ฌโใจใใ
 *
 * ๅคๅฅๅผใ0ใฎใจใใ1ใคใฎใใ
 * ๅคๅฅๅผใ0ใใๅคงใใๆใ2็นใงไบคใใใtใๅฐใใๆนใๆๅใซใชใใ
 * ไบคใใใชใๅ ดๅใฏๆฑบใๆใกใงtใ-1ใซใใใtใใใคใในใจใใใใจใฏ่ฆ็นใฎๅพใใซใใใ
 */
double	calc_t_sphere(t_ray *ray, t_sphere	*sphere)
{
	double	a;
	double	b;
	double	c;
	double	dif;
	t_vec3	*s;

	s = vec3_sub(ray->start_vec, sphere->center);
	a = pow(vec3_norm(ray->direction_vec), 2);
	b = 2 * vec3_inner_product(s, ray->direction_vec);
	c = pow(vec3_norm(s), 2) - pow(sphere->diameter / 2, 2);
	dif = pow(b, 2) - 4 * a * c;
	free(s);
	if (dif < 0)
		return (-1);
	return ((-b - sqrt(dif)) / (2 * a));
}
