/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:16:35 by takkatao          #+#    #+#             */
/*   Updated: 2022/05/31 14:55:11 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

/*
 * vupを計算する。vupはカメラの上方向のベクトル。
 * カメラはz軸の正方向を上にしているとする。
 * カメラの視線ベクトルとvupが並行になってしまうと外積が0になってしまうため、少し角度をつける。
 */
t_vec3	*calc_vup(t_vec3 *camera_ray)
{
	double	sum;

	if (camera_ray->x == 0 && camera_ray->y == 0)
	{
		sum = sqrt(pow(0.1, 2) + 1);
		return (vector3(0, 0.1 / sum, 1 / sum));
	}
	return (vector3(0, 0, 1));
}

t_vec3	*calc_u_base(t_vec3	*camera_ray)
{
	t_vec3	*u_base;
	t_vec3	*vup;
	t_vec3	*tmp1;

	vup = calc_vup(camera_ray);
	tmp1 = vec3_outer_product(vup, camera_ray);
	u_base = vec3_normalize(tmp1);
	free(vup);
	free(tmp1);
	return (u_base);
}

t_vec3	*calc_u(t_scene *scene, t_vec3	*camera_ray, double x)
{
	t_vec3	*u;
	t_vec3	*u_base;
	double	screen_width;

	screen_width = 2 * tan(M_PI * scene->camera->fov / 180 / 2);
	u_base = calc_u_base(camera_ray);
	u = vec3_multiply(u_base, screen_width - 2 * screen_width * x / W);
	free(u_base);
	return (u);
}

t_vec3	*calc_v(t_scene *scene, t_vec3	*camera_ray, double y)
{
	t_vec3	*v;
	t_vec3	*v_base;
	t_vec3	*u_base;
	t_vec3	*tmp1;
	double	screen_width;

	screen_width = 2 * tan(M_PI * scene->camera->fov / 180 / 2);
	u_base = calc_u_base(camera_ray);
	tmp1 = vec3_outer_product(u_base, camera_ray);
	v_base = vec3_normalize(tmp1);
	v = vec3_multiply(v_base, -1 * screen_width + 2 * screen_width * y / H);
	free(tmp1);
	free(u_base);
	free(v_base);
	return (v);
}

/*
 * スクリーン座標をワールド座標に変換。
 * minilibXのpixelを3次元上のスクリーンに変換。
 * カメラからスクリーンの距離は1で固定。
 * u,vはスクリーン上での基底ベクトル。基底ベクトルはvupと直交するように設定する。
 */
t_vec3	*to_screen_vec(t_scene *scene, double x, double y)
{
	t_vec3	*vec;
	t_vec3	*camera_ray;
	t_vec3	*u;
	t_vec3	*v;

	camera_ray = calc_camera_ray(scene);
	u = calc_u(scene, camera_ray, x);
	v = calc_v(scene, camera_ray, y);
	vec = vec3_add4(scene->camera->point, camera_ray, u, v);
	free(camera_ray);
	free(u);
	free(v);
	return (vec);
}
