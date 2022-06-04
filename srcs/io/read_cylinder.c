/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:42:14 by takkatao          #+#    #+#             */
/*   Updated: 2022/06/04 16:24:46 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

t_object	*read_cylinder(char	**splitted_line)
{
	t_object	*object;
	t_cylinder	*cylinder;

	if (count_splits(splitted_line) != 6)
		puterr_exit("cylinder illegal format");
	cylinder = (t_cylinder *)ft_xcalloc(1, sizeof(t_cylinder));
	cylinder->point = gen_vec3_from_line(splitted_line[1]);
	cylinder->orientation_vec = gen_vec3_from_line(splitted_line[2]);
	cylinder->orientation_vec = vec3_normalize(cylinder->orientation_vec);
	cylinder->radius = atod_validatiton_wrapper(splitted_line[3]) / 2;
	cylinder->height = atod_validatiton_wrapper(splitted_line[4]);
	cylinder->color = get_color_from_line(splitted_line[5]);
	object = (t_object *) ft_xcalloc(1, sizeof(t_object));
	object->ptr = cylinder;
	object->type = T_CYLINDER;
	return (object);
}
