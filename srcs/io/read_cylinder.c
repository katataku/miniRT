/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:42:14 by takkatao          #+#    #+#             */
/*   Updated: 2022/05/17 16:42:14 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

// TODO:atof自作関数に置き換える。
void	read_cylinder(t_scene *scene, char	**splitted_line)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)ft_xcalloc(1, sizeof(t_cylinder));
	cylinder->coordinates = gen_vec3_from_line(splitted_line[1]);
	cylinder->orientation_vector = gen_vec3_from_line(splitted_line[2]);
	cylinder->cylinder_diameter = atof(splitted_line[3]);
	cylinder->cylinder_height = atof(splitted_line[4]);
	cylinder->color = get_color_from_line(splitted_line[5]);
	scene->cylinder = cylinder;
}
