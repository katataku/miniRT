/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:41:50 by takkatao          #+#    #+#             */
/*   Updated: 2022/06/03 09:31:45 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

t_object	*read_sphere(char	**splitted_line)
{
	t_object	*object;
	t_sphere	*sphere;

	sphere = (t_sphere *)ft_xcalloc(1, sizeof(t_sphere));
	sphere->center = gen_vec3_from_line(splitted_line[1]);
	sphere->diameter = ft_atod(splitted_line[2]);
	sphere->color = get_color_from_line(splitted_line[3]);
	object = (t_object *) ft_xcalloc(1, sizeof(t_object));
	object->ptr = sphere;
	object->type = T_SPHERE;
	return (object);
}
