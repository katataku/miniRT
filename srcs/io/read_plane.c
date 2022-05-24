/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:39:53 by takkatao          #+#    #+#             */
/*   Updated: 2022/05/24 15:55:22 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

t_object	*read_plane(char	**splitted_line)
{
	t_object	*object;
	t_plane		*plane;

	plane = (t_plane *)ft_xcalloc(1, sizeof(t_plane));
	plane->point = gen_vec3_from_line(splitted_line[1]);
	plane->orientation_vector = gen_vec3_from_line(splitted_line[2]);
	plane->color = get_color_from_line(splitted_line[3]);
	object = (t_object *) ft_xcalloc(1, sizeof(t_object));
	object->ptr = plane;
	object->identifier = T_PLANE;
	return (object);
}
