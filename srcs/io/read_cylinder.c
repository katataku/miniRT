/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:42:14 by takkatao          #+#    #+#             */
/*   Updated: 2022/05/27 17:43:37 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

// TODO:atof自作関数に置き換える。
void	read_cylinder(t_scene *scene, char	**splitted_line)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)ft_xcalloc(1, sizeof(t_cylinder));
	cylinder->point = gen_vec3_from_line(splitted_line[1]);
	cylinder->orientation_vec = gen_vec3_from_line(splitted_line[2]);
	cylinder->diameter = ft_atod(splitted_line[3]);
	cylinder->height = ft_atod(splitted_line[4]);
	cylinder->color = get_color_from_line(splitted_line[5]);
	scene->cylinder = cylinder;
}
