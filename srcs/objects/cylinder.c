/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 14:23:44 by ahayashi          #+#    #+#             */
/*   Updated: 2022/05/31 12:01:26 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

double	calc_lambert_cos_cylinder(t_ray *ray, t_cylinder *cylinder, t_light *light)
{
	double	cos;
	double	h;
	t_vec3	*center;
	t_vec3	*n_vec;
	t_vec3	*l_vec;

	h = sqrt(pow(vec3_norm(vec3_sub(ray->p_vec, cylinder->point)), 2) - pow(cylinder->radius, 2));
	center = vec3_add(cylinder->point, vec3_multiply(cylinder->orientation_vec, h));
	if (ray->t_type == T_T1)
		n_vec = vec3_sub(ray->p_vec, center);
	else
		n_vec = vec3_sub(center, ray->p_vec);
	l_vec = vec3_sub(light->point, ray->p_vec);
	cos = cos_of_angles(n_vec, l_vec);
	if (cos < 0)
		return (0);
	return (cos);
}

double	calc_a(t_ray *ray, t_cylinder	*cylinder)
{
	t_vec3	*d_cross_n;
	double	outer_norm;
	double	a;

	d_cross_n = vec3_outer_product(ray->direction_vec, cylinder->orientation_vec);
	outer_norm = vec3_norm(d_cross_n);
	a = pow(outer_norm, 2);
	return (a);
}

double	calc_b(t_ray *ray, t_cylinder	*cylinder)
{
	t_vec3	*d_cross_n;
	t_vec3	*s_minus_c_cross_n;
	t_vec3	*s_minus_c;
	double	b;

	d_cross_n = vec3_outer_product(ray->direction_vec, cylinder->orientation_vec);
	s_minus_c = vec3_sub(ray->start_vec, cylinder->point);
	s_minus_c_cross_n = vec3_outer_product(s_minus_c, cylinder->orientation_vec);
	b = 2 * vec3_inner_product(d_cross_n, s_minus_c_cross_n);
	return (b);
}

double	calc_c(t_ray *ray, t_cylinder	*cylinder)
{
	t_vec3	*s_minus_c_cross_n;
	t_vec3	*s_minus_c;
	double	c;

	s_minus_c = vec3_sub(ray->start_vec, cylinder->point);
	s_minus_c_cross_n = vec3_outer_product(s_minus_c, cylinder->orientation_vec);
	c = pow(vec3_norm(s_minus_c_cross_n), 2) - pow(cylinder->radius, 2);
	return (c);
}

double	calc_h(t_vec3 *p, t_cylinder	*cylinder)
{
	double	h;

	h = sqrt(pow(vec3_norm(vec3_sub(p, cylinder->point)), 2) - pow(cylinder->radius, 2));
	return (h);
}

static double	calc_t_(double t1, double t2, t_ray *ray, t_cylinder *cylinder)
{
	t_vec3	*p1;
	t_vec3	*p2;
	double	h1;
	double	h2;

	p1 = vec3_add(ray->start_vec, vec3_multiply(ray->direction_vec, t1));
	h1 = calc_h(p1, cylinder);
	if (h1 <= cylinder->height)
	{
		ray->p_vec = p1;
		ray->t = t1;
		ray->t_type = T_T1;
		return (t1);
	}
	p2 = vec3_add(ray->start_vec, vec3_multiply(ray->direction_vec, t2));
	h2 = calc_h(p2, cylinder);
	if (h2 <= cylinder->height)
	{
		ray->p_vec = p2;
		ray->t = t2;
		ray->t_type = T_T2;
		return (t2);
	}
	ray->t_type = T_NOT_CROSS;
	return (-1);
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
	return (calc_t_( (-b - sqrt(dif)) / (2 * a), (-b + sqrt(dif)) / (2 * a), ray, cylinder));
}
