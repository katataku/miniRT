/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 16:34:31 by takkatao          #+#    #+#             */
/*   Updated: 2022/06/04 17:48:52 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

int	count_splits(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}

int	get_color_from_line(char *color_line)
{
	char	**splitted_color_line;
	int		color;
	int		i;

	splitted_color_line = ft_xsplit(color_line, ',');
	if (count_splits(splitted_color_line) != 3)
		puterr_exit("color must be R,G,B format");
	color = make_color_from_trgb(255, \
			atoi_color(splitted_color_line[0]), \
			atoi_color(splitted_color_line[1]), \
			atoi_color(splitted_color_line[2]));
	i = -1;
	while (splitted_color_line[++i] != NULL)
		free(splitted_color_line[i]);
	free(splitted_color_line);
	return (color);
}

t_vec3	*gen_pos_vec3_from_line(char *vec_line)
{
	char	**splitted_vec_line;
	t_vec3	*rtv;
	int		i;

	splitted_vec_line = ft_xsplit(vec_line, ',');
	if (count_splits(splitted_vec_line) != 3)
		puterr_exit("vecotr must be x,y,z format");
	rtv = vector3(\
			atod_validatiton_wrapper(splitted_vec_line[0]), \
			atod_validatiton_wrapper(splitted_vec_line[1]), \
			atod_validatiton_wrapper(splitted_vec_line[2]));
	i = -1;
	while (splitted_vec_line[++i] != NULL)
		free(splitted_vec_line[i]);
	free(splitted_vec_line);
	return (rtv);
}

t_vec3	*gen_orientation_vec3_from_line(char *vec_line)
{
	char	**splitted_vec_line;
	t_vec3	*rtv;
	int		i;

	splitted_vec_line = ft_xsplit(vec_line, ',');
	if (count_splits(splitted_vec_line) != 3)
		puterr_exit("vecotr must be x,y,z format");
	rtv = vector3(\
			atod_orientation_vector(splitted_vec_line[0]), \
			atod_orientation_vector(splitted_vec_line[1]), \
			atod_orientation_vector(splitted_vec_line[2]));
	i = -1;
	while (splitted_vec_line[++i] != NULL)
		free(splitted_vec_line[i]);
	free(splitted_vec_line);
	return (rtv);
}
