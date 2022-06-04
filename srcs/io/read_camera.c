/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:41:03 by takkatao          #+#    #+#             */
/*   Updated: 2022/06/04 17:50:36 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

void	read_camera(t_scene *scene, char	**splitted_line)
{
	t_camera	*camera;
	t_vec3		*tmp;

	if (scene->camera != NULL)
		puterr_exit("camera must be 1");
	if (count_splits(splitted_line) != 4)
		puterr_exit("camera illegal format");
	camera = (t_camera *)ft_xcalloc(1, sizeof(t_camera));
	camera->point = gen_pos_vec3_from_line(splitted_line[1]);
	tmp = gen_orientation_vec3_from_line(splitted_line[2]);
	camera->orientation_vec = vec3_normalize(tmp);
	free(tmp);
	camera->fov = atoi_fov(splitted_line[3]);
	scene->camera = camera;
}
