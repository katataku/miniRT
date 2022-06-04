/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:41:22 by takkatao          #+#    #+#             */
/*   Updated: 2022/06/04 16:24:58 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

void	read_light(t_scene *scene, char	**splitted_line)
{
	t_light	*light;

	if (scene->light != NULL)
		puterr_exit("light must be 1");
	if (count_splits(splitted_line) != 4)
		puterr_exit("light illegal format");
	light = (t_light *)ft_xcalloc(1, sizeof(t_light));
	light->point = gen_vec3_from_line(splitted_line[1]);
	light->ratio = atod_validatiton_wrapper(splitted_line[2]);
	light->color = get_color_from_line(splitted_line[3]);
	scene->light = light;
}
