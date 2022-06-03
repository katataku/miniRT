/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:41:22 by takkatao          #+#    #+#             */
/*   Updated: 2022/06/03 09:31:48 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

void	read_light(t_scene *scene, char	**splitted_line)
{
	t_light	*light;

	light = (t_light *)ft_xcalloc(1, sizeof(t_light));
	light->point = gen_vec3_from_line(splitted_line[1]);
	light->ratio = ft_atod(splitted_line[2]);
	light->color = get_color_from_line(splitted_line[3]);
	scene->light = light;
}
