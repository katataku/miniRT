/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:41:03 by takkatao          #+#    #+#             */
/*   Updated: 2022/06/04 16:22:02 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

void	read_camera(t_scene *scene, char	**splitted_line)
{
	t_camera	*camera;

	if (scene->camera != NULL)
		puterr_exit("camera must be 1");
	if (count_splits(splitted_line) != 4)
		puterr_exit("camera illegal format");
	camera = (t_camera *)ft_xcalloc(1, sizeof(t_camera));
	camera->point = gen_vec3_from_line(splitted_line[1]);
	camera->orientation_vec = gen_vec3_from_line(splitted_line[2]);
	camera->orientation_vec = vec3_normalize(camera->orientation_vec);
	camera->fov = atoi_fov(splitted_line[3]);
	scene->camera = camera;
}
