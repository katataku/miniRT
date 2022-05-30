/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 14:23:44 by ahayashi          #+#    #+#             */
/*   Updated: 2022/05/30 14:38:30 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

double	calc_lambert_cos_cylinder(t_ray *ray, t_cylinder *cylinder, t_light *light)
{
	double	cos;
	double	t;
	double	h;
	t_vec3	*center;
	t_vec3	*p_vec;
	t_vec3	*n_vec;
	t_vec3	*l_vec;

	t = calc_t_cylinder(ray, cylinder);
	p_vec = vec3_add(ray->start_vec, vec3_multiply(ray->direction_vec, t));
	h = sqrt(pow(vec3_norm(vec3_sub(p_vec, cylinder->point)), 2) - pow(cylinder->radius, 2));
	center = vec3_add(cylinder->point, vec3_multiply(cylinder->orientation_vec, h));
	n_vec = vec3_sub(p_vec, center);
	l_vec = vec3_sub(light->point, p_vec);
	cos = cos_of_angles(n_vec, l_vec);
	double sin = vec3_norm(vec3_outer_product(n_vec, l_vec))/(vec3_norm(n_vec) * vec3_norm(l_vec));
	if (sin < 0)
	{
		n_vec = vec3_sub(center, p_vec);
		l_vec = vec3_sub(light->point, p_vec);
		cos = cos_of_angles(n_vec, l_vec);
	}

	if (cos < 0)
		return (0);
	return (cos);
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
	t_vec3	*d_cross_n;
	t_vec3	*s_minus_c_cross_n;
	t_vec3	*p;
	t_vec3	*p2;
	double	outer_norm;
	double	a;
	double	b;
	double	c;
	double	dif;

	d_cross_n = vec3_outer_product(ray->direction_vec, cylinder->orientation_vec);
	outer_norm = vec3_norm(d_cross_n);
	a = pow(outer_norm, 2);
	p = vec3_sub(ray->start_vec, cylinder->point);
	s_minus_c_cross_n = vec3_outer_product(p, cylinder->orientation_vec);
	b = 2 * vec3_inner_product(d_cross_n, s_minus_c_cross_n);
	c = pow(vec3_norm(s_minus_c_cross_n), 2) - pow(cylinder->radius, 2);
	dif = pow(b, 2) - 4 * a * c;
	if (dif < 0 || a == 0)
		return (-1);
	double t1 = (-b - sqrt(dif)) / (2 * a);
	double t2 = (-b + sqrt(dif)) / (2 * a);

	t_vec3 *p1;
	p1 = vec3_add(ray->start_vec, vec3_multiply(ray->direction_vec, t1));
	p2 = vec3_add(ray->start_vec, vec3_multiply(ray->direction_vec, t2));
	double h1 = sqrt(pow(vec3_norm(vec3_sub(p1, cylinder->point)), 2) - pow(cylinder->radius, 2));
	if (h1 <= cylinder->height)
		return (t1);
	double h2 = sqrt(pow(vec3_norm(vec3_sub(p2, cylinder->point)), 2) - pow(cylinder->radius, 2));
	if (h2 <= cylinder->height)
		return (t2);
	return (-1);
}
