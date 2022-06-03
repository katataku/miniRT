/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:34:31 by takkatao          #+#    #+#             */
/*   Updated: 2022/06/03 09:30:11 by takkatao         ###   ########.fr       */
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
	int		i;

	splitted_vec_line = ft_xsplit(vec_line, ',');
	rtv = vector3(\
			ft_atod(splitted_vec_line[0]), \
			ft_atod(splitted_vec_line[1]), \
			ft_atod(splitted_vec_line[2]));
	i = -1;
	while (splitted_vec_line[++i] != NULL)
		free(splitted_vec_line[i]);
	free(splitted_vec_line);
	return (rtv);
}
