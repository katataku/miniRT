/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:34:31 by takkatao          #+#    #+#             */
/*   Updated: 2022/05/27 14:19:41 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

int	get_color_from_line(char *color_line)
{
	char	**splitted_color_line;
	int		color;
	int		i;

	splitted_color_line = ft_xsplit(color_line, ',');
	color = make_color_from_trgb(255, \
			atoi(splitted_color_line[0]), \
			atoi(splitted_color_line[1]), \
			atoi(splitted_color_line[2]));
	i = -1;
	while (splitted_color_line[++i] != NULL)
		free(splitted_color_line[i]);
	free(splitted_color_line);
	return (color);
}

t_vec3	*gen_vec3_from_line(char *vec_line)
{
	char	**splitted_vec_line;
	t_vec3	*rtv;

	splitted_vec_line = ft_xsplit(vec_line, ',');
	rtv = vector3(\
			atof(splitted_vec_line[0]), \
			atof(splitted_vec_line[1]), \
			atof(splitted_vec_line[2]));
	return (rtv);
}
