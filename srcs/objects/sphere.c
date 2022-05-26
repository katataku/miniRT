/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:30:16 by ahayashi          #+#    #+#             */
/*   Updated: 2022/05/26 23:32:34 by takkatao         ###   ########.fr       */
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
 * 𝑡 =(−𝐵±√(𝐵^2−4𝐴𝐶))/2𝐴
 *
 * 𝐴 = |𝐝⃗|^2
 * 𝐵 = 2(𝐬⃗⋅𝐝⃗)
 * 𝐶 = |𝐬⃗|^2−𝑟^2
 * ※球が原点にあるとき。球の中心が原点に重なるように平行移動してあげれば良いので
 * カメラの位置ベクトルから球の中心の位置ベクトルを引いたものを𝐬⃗とする
 *
 * 判別式が0のとき、1つのする
 * 判別式が0より大きい時、2点で交わる。tが小さい方が手前になる。
 * 交わらない場合は決め打ちでtを-1にする。tがマイナスということは視点の後ろにある。
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
	if (dif < 0)
		return (-1);
	return ((-b - sqrt(dif)) / (2 * a));
}
