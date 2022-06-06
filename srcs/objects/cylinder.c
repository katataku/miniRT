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
 * 𝑡 =(−𝐵±√(𝐵^2−4𝐴𝐶))/2𝐴
 *
 * 𝐴 = |𝐝⃗×𝐧⃗|^2
 * 𝐵 = 2{(𝐝⃗×𝐧⃗)･(𝐬⃗-c⃗)×𝐧⃗}
 * 𝐶 = |(𝐬⃗-c⃗)×𝐧⃗|^2−𝑟^2
 * 円筒の側面の中心の位置ベクトルがC。
 * |𝐧⃗| = 1
 *
 * 判別式が0のとき、1つのする
 * 判別式が0より大きい時、2点で交わる。tが小さい方が手前になる。
 * 交わらない場合は決め打ちでtを-1にする。tがマイナスということは視点の後ろにある。
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
