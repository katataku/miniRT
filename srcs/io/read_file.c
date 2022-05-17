/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:03:51 by takkatao          #+#    #+#             */
/*   Updated: 2022/05/16 18:10:55 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

int	get_color_from_line(char *color_line)
{
	char	**splitted_color_line;
	int		color;

	splitted_color_line = ft_xsplit(color_line, ',');
	color = make_color_from_trgb(255, \
			atoi(splitted_color_line[0]), \
			atoi(splitted_color_line[1]), \
			atoi(splitted_color_line[2]));
	return (color);
}

// TODO:atof自作関数に置き換える。
void	read_a(t_scene *scene, char	**splitted_line)
{
	t_ambient_lightning	*ambient;

	ambient = (t_ambient_lightning *)ft_xcalloc(1, sizeof(t_ambient_lightning));
	ambient->lighting_ratio = atof(splitted_line[1]);
	ambient->color = get_color_from_line(splitted_line[2]);
	scene->ambient_lightning = ambient;
}

static void	read_element(t_scene *scene, char *line)
{
	char	**splitted_line;

	splitted_line = ft_xsplit(line, ' ');
	(void)scene;
	if (ft_strcmp(splitted_line[0], "A") == 0)
		read_a(scene, splitted_line);
	if (ft_strcmp(splitted_line[0], "C") == 0)
		printf("camera\n");
	if (ft_strcmp(splitted_line[0], "L") == 0)
		printf("light\n");
	if (ft_strcmp(splitted_line[0], "sp") == 0)
		printf("sp\n");
	if (ft_strcmp(splitted_line[0], "pl") == 0)
		printf("pl\n");
	if (ft_strcmp(splitted_line[0], "cy") == 0)
		printf("cy\n");
}

t_scene	*read_file(char **argv)
{
	t_scene	*scene;
	int		fd;
	char	*line[1024];

	scene = (t_scene *)ft_xcalloc(1, sizeof(t_scene));
	fd = xopen(argv[1], O_RDONLY, 0);
	while (get_next_line(fd, line))
		read_element(scene, *line);
	xclose(fd);
	scene->camera = (t_camera *)ft_xcalloc(1, sizeof(t_camera));
	scene->camera->view_point = vector3(0.0, 0.0, 10.0);
	scene->ambient_lightning = (t_ambient_lightning *) ft_xcalloc(1, sizeof(t_ambient_lightning));
	scene->ambient_lightning->lighting_ratio = 0.8;
	scene->ambient_lightning->color = 0xFF00FFFF;
	scene->light = (t_light *) ft_xcalloc(1, sizeof(t_light));
	scene->light->light_point = vector3(0.0, 0.0, 0.0);
	scene->sphere = (t_sphere *) ft_xcalloc(1, sizeof(t_sphere));
	scene->sphere->sphere_center = vector3(3.0, 3.0, 0.0);
	scene->sphere->diameter = 1;
	scene->sphere->color = 0xFF00FFFF;
	return (scene);
}
