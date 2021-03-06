/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 14:23:44 by ahayashi          #+#    #+#             */
/*   Updated: 2022/06/04 22:12:33 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static double	calc_a(t_ray *ray, t_cylinder	*cy)
{
	t_vec3	*d_cross_n;
	double	outer_norm;
	double	a;

	d_cross_n = vec3_outer_product(ray->direction_vec, cy->orientation_vec);
	outer_norm = vec3_norm(d_cross_n);
	a = pow(outer_norm, 2);
	free(d_cross_n);
	return (a);
}

static double	calc_b(t_ray *ray, t_cylinder *cy)
{
	t_vec3	*d_cross_n;
	t_vec3	*s_minus_c_cross_n;
	t_vec3	*s_minus_c;
	double	b;

	d_cross_n = vec3_outer_product(ray->direction_vec, cy->orientation_vec);
	s_minus_c = vec3_sub(ray->start_vec, cy->point);
	s_minus_c_cross_n = vec3_outer_product(s_minus_c, cy->orientation_vec);
	b = 2 * vec3_inner_product(d_cross_n, s_minus_c_cross_n);
	free(d_cross_n);
	free(s_minus_c);
	free(s_minus_c_cross_n);
	return (b);
}

static double	calc_c(t_ray *ray, t_cylinder	*cy)
{
	t_vec3	*s_minus_c_cross_n;
	t_vec3	*s_minus_c;
	double	c;

	s_minus_c = vec3_sub(ray->start_vec, cy->point);
	s_minus_c_cross_n = vec3_outer_product(s_minus_c, cy->orientation_vec);
	c = pow(vec3_norm(s_minus_c_cross_n), 2) - pow(cy->radius, 2);
	free(s_minus_c);
	free(s_minus_c_cross_n);
	return (c);
}

/*
 * ๐ก =(โ๐ตยฑโ(๐ต^2โ4๐ด๐ถ))/2๐ด
 *
 * ๐ด = |๐โร๐งโ|^2
 * ๐ต = 2{(๐โร๐งโ)๏ฝฅ(๐ฌโ-cโ)ร๐งโ}
 * ๐ถ = |(๐ฌโ-cโ)ร๐งโ|^2โ๐^2
 * ๅ็ญใฎๅด้ขใฎไธญๅฟใฎไฝ็ฝฎใใฏใใซใCใ
 * |๐งโ| = 1
 *
 * ๅคๅฅๅผใ0ใฎใจใใ1ใคใฎใใ
 * ๅคๅฅๅผใ0ใใๅคงใใๆใ2็นใงไบคใใใtใๅฐใใๆนใๆๅใซใชใใ
 * ไบคใใใชใๅ?ดๅใฏๆฑบใๆใกใงtใ-1ใซใใใtใใใคใในใจใใใใจใฏ่ฆ็นใฎๅพใใซใใใ
 */
double	calc_t_cylinder(t_ray *ray, t_cylinder	*cylinder)
{
	double	a;
	double	b;
	double	c;
	double	dif;

	a = calc_a(ray, cylinder);
	b = calc_b(ray, cylinder);
	c = calc_c(ray, cylinder);
	dif = pow(b, 2) - 4 * a * c;
	if (dif < 0 || a == 0)
		return (-1);
	return (decide_t((-b - sqrt(dif)) / (2 * a), \
		(-b + sqrt(dif)) / (2 * a), \
		ray, cylinder));
}

enum e_t_type	calc_t_type(t_ray *ray, t_cylinder	*cylinder)
{
	double	a;
	double	b;
	double	c;
	double	dif;

	a = calc_a(ray, cylinder);
	b = calc_b(ray, cylinder);
	c = calc_c(ray, cylinder);
	dif = pow(b, 2) - 4 * a * c;
	if (dif < 0 || a == 0)
		return (-1);
	return (decide_t_type((-b - sqrt(dif)) / (2 * a), \
		(-b + sqrt(dif)) / (2 * a), \
		ray, cylinder));
}
