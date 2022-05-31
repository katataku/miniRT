/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:14:18 by takkatao          #+#    #+#             */
/*   Updated: 2022/05/31 14:55:03 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

/*
 * カメラから見る方向への、正規化されたrayを計算する
 * カメラの位置(lookfrom)は入力ファイルのview_pointから設定。
 * カメラの見る向きは入力ファイルのorientation_vecの向きに設定。
 */
t_vec3	*calc_camera_ray(t_scene *scene)
{
	t_vec3	*lookat;
	t_vec3	*lookfrom;
	t_vec3	*camera_ray;
	t_vec3	*camera_ray_norm;

	lookfrom = scene->camera->point;
	lookat = vec3_add(lookfrom, scene->camera->orientation_vec);
	camera_ray = vec3_sub(lookat, lookfrom);
	camera_ray_norm = vec3_normalize(camera_ray);
	free(lookat);
	free(camera_ray);
	return (camera_ray_norm);
}
