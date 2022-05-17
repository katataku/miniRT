/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:39:53 by takkatao          #+#    #+#             */
/*   Updated: 2022/05/17 16:40:09 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

void	read_plane(t_scene *scene, char	**splitted_line)
{
	t_plane	*plane;

	plane = (t_plane *)ft_xcalloc(1, sizeof(t_plane));
	plane->coordinates = gen_vec3_from_line(splitted_line[1]);
	plane->orientation_vector = gen_vec3_from_line(splitted_line[2]);
	plane->color = get_color_from_line(splitted_line[3]);
	scene->plane = plane;
}
