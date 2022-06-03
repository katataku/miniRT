/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ambient.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:40:39 by takkatao          #+#    #+#             */
/*   Updated: 2022/06/03 09:31:33 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

void	read_ambient(t_scene *scene, char	**splitted_line)
{
	t_ambient_light	*ambient;

	ambient = (t_ambient_light *)ft_xcalloc(1, sizeof(t_ambient_light));
	ambient->ratio = ft_atod(splitted_line[1]);
	ambient->color = get_color_from_line(splitted_line[2]);
	scene->ambient_light = ambient;
}
