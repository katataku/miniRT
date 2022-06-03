/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:41:03 by takkatao          #+#    #+#             */
/*   Updated: 2022/06/03 09:31:31 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

void	read_camera(t_scene *scene, char	**splitted_line)
{
	t_camera	*camera;

	camera = (t_camera *)ft_xcalloc(1, sizeof(t_camera));
	camera->point = gen_vec3_from_line(splitted_line[1]);
	camera->orientation_vec = gen_vec3_from_line(splitted_line[2]);
	camera->orientation_vec = vec3_normalize(camera->orientation_vec);
	camera->fov = ft_atod(splitted_line[3]);
	scene->camera = camera;
}
