/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 14:23:44 by ahayashi          #+#    #+#             */
/*   Updated: 2022/05/29 14:23:44 by ahayashi         ###   ########.jp       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

double	calc_lambert_cos_cylinder(t_ray *ray, t_cylinder *cylinder, t_light *light)
{
	(void)ray;
	(void)cylinder;
	(void)light;
	return (0);
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
double	calc_t_cylinder(t_ray *ray, t_cylinder	*cylinder)
{
	(void)ray;
	(void)cylinder;
	return (0);
}
