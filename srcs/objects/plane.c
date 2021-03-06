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
 * 𝑡 = −(𝐬⃗⋅𝐧⃗)/(𝐝⃗⋅𝐧⃗)
 *
 * 分母が0より小さいときは解なし。
 * ※平面が原点にあるとき。カメラの位置ベクトルから平面上の任意の点の位置ベクトルを引いたものを𝐬⃗とする
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
 * 拡散反射光を計算する。
 * cosの値がマイナスになる場合は光が当たっていないとして扱う
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
