/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:41:50 by takkatao          #+#    #+#             */
/*   Updated: 2022/05/17 16:41:52 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

// TODO:atof自作関数に置き換える。
void	read_sphere(t_scene *scene, char	**splitted_line)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)ft_xcalloc(1, sizeof(t_sphere));
	sphere->sphere_center = gen_vec3_from_line(splitted_line[1]);
	sphere->diameter = atof(splitted_line[2]);
	sphere->color = get_color_from_line(splitted_line[3]);
	scene->sphere = sphere;
}
