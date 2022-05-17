/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:03:51 by takkatao          #+#    #+#             */
/*   Updated: 2022/05/17 14:51:42 by takkatao         ###   ########.fr       */
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

t_vec3	*get_vec3_from_line(char *vec_line)
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

// TODO:atof自作関数に置き換える。
void	read_ambient(t_scene *scene, char	**splitted_line)
{
	t_ambient_lightning	*ambient;

	ambient = (t_ambient_lightning *)ft_xcalloc(1, sizeof(t_ambient_lightning));
	ambient->lighting_ratio = atof(splitted_line[1]);
	ambient->color = get_color_from_line(splitted_line[2]);
	scene->ambient_lightning = ambient;
}

void	read_camera(t_scene *scene, char	**splitted_line)
{
	t_camera	*camera;

	camera = (t_camera *)ft_xcalloc(1, sizeof(t_camera));
	camera->view_point = get_vec3_from_line(splitted_line[1]);
	camera->orientation_vector = get_vec3_from_line(splitted_line[2]);
	camera->fov = atof(splitted_line[3]);
	scene->camera = camera;
}

static void	read_element(t_scene *scene, char *line)
{
	char	**splitted_line;

	splitted_line = ft_xsplit(line, ' ');
	(void)scene;
	if (ft_strcmp(splitted_line[0], "A") == 0)
		read_ambient(scene, splitted_line);
	if (ft_strcmp(splitted_line[0], "C") == 0)
		read_camera(scene, splitted_line);
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
	scene->camera->view_point = vector3(0.0, 0.0, 10.0);
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
