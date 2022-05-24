/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:30:16 by ahayashi          #+#    #+#             */
/*   Updated: 2022/05/24 14:30:16 by ahayashi         ###   ########.jp       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

/*
 * 拡散反射光を計算する。
 */
int	calc_diffuse_light_sphere(t_ray *ray, t_sphere *sphere, t_light *light)
{
	double	t;
	double	cos;
	t_vec3	*p_vec;
	t_vec3	*n_vec;
	t_vec3	*l_vec;

	t = calc_t_sphere(ray, sphere);
	p_vec = vec3_add(ray->start_vector, vec3_multiply(ray->direction_vector, t));
	n_vec = vec3_sub(p_vec, sphere->sphere_center);
	l_vec = vec3_sub(light->light_point, p_vec);
	cos = cos_of_angles(n_vec, l_vec);
	if (cos <= 0)
		return (0);
	return (make_color_from_trgb(
			get_trgb(light->color, TRANSPARENT),
			get_trgb(light->color, RED) * light->brightness_ratio * cos,
			get_trgb(light->color, GREEN) * light->brightness_ratio * cos,
			get_trgb(light->color, BLUE) * light->brightness_ratio * cos));
}

/*
 * レイと球が交差するか判定する関数。
 *
 * 判別式が0のとき、1つのする
 * 判別式が0より大きい時、2点で交わる。tが小さい方が手前になる。
 */
bool	is_cross_sphere(t_ray *ray, t_sphere *sphere)
{
	return (calc_t_sphere(ray, sphere) >= 0);
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

	s = vec3_sub(ray->start_vector, sphere->sphere_center);
	a = pow(vec3_norm(ray->direction_vector), 2);
	b = 2 * vec3_inner_product(s, ray->direction_vector);
	c = pow(vec3_norm(s), 2) - pow(sphere->diameter / 2, 2);
	dif = pow(b, 2) - 4 * a * c;
	if (dif < 0)
		return (-1);
	return ((-b - sqrt(dif)) / (2 * a));
}
