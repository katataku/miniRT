/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ambient.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:40:39 by takkatao          #+#    #+#             */
/*   Updated: 2022/06/04 16:19:33 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

void	read_ambient(t_scene *scene, char	**splitted_line)
{
	t_ambient_light	*ambient;

	if (scene->ambient_light != NULL)
		puterr_exit("ambient light must be 1");
	if (count_splits(splitted_line) != 3)
		puterr_exit("ambient light illegal format");
	ambient = (t_ambient_light *)ft_xcalloc(1, sizeof(t_ambient_light));
	ambient->ratio = atod_ratio(splitted_line[1]);
	ambient->color = get_color_from_line(splitted_line[2]);
	scene->ambient_light = ambient;
}
