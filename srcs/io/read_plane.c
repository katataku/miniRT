/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:39:53 by takkatao          #+#    #+#             */
/*   Updated: 2022/06/04 16:18:02 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

t_object	*read_plane(char	**splitted_line)
{
	t_object	*object;
	t_plane		*plane;

	if (count_splits(splitted_line) != 4)
		puterr_exit("plane illegal format");
	plane = (t_plane *)ft_xcalloc(1, sizeof(t_plane));
	plane->point = gen_vec3_from_line(splitted_line[1]);
	plane->normal_vec = gen_vec3_from_line(splitted_line[2]);
	plane->color = get_color_from_line(splitted_line[3]);
	object = (t_object *) ft_xcalloc(1, sizeof(t_object));
	object->ptr = plane;
	object->type = T_PLANE;
	return (object);
}
