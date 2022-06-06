/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:03:51 by takkatao          #+#    #+#             */
/*   Updated: 2022/06/04 22:09:22 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

static void	read_element(t_scene *scene, char *line)
{
	char		**splitted_line;
	t_object	*object;
	int			i;

	object = NULL;
	splitted_line = ft_xsplit(line, ' ');
	if (ft_strcmp(splitted_line[0], "A") == 0)
		read_ambient(scene, splitted_line);
	if (ft_strcmp(splitted_line[0], "C") == 0)
		read_camera(scene, splitted_line);
	if (ft_strcmp(splitted_line[0], "L") == 0)
		read_light(scene, splitted_line);
	if (ft_strcmp(splitted_line[0], "sp") == 0)
		object = read_sphere(splitted_line);
	if (ft_strcmp(splitted_line[0], "pl") == 0)
		object = read_plane(splitted_line);
	if (ft_strcmp(splitted_line[0], "cy") == 0)
		object = read_cylinder(splitted_line);
	if (object != NULL)
		ft_lstadd_back(&(scene->objects), ft_lstnew(object));
	i = -1;
	while (splitted_line[++i] != NULL)
		free(splitted_line[i]);
	free(splitted_line);
}

double	calc_dist(t_vec3 *a, t_vec3 *b)
{
	t_vec3	*sub;
	double	rtv;

	sub = vec3_sub(a, b);
	rtv = vec3_norm(sub);
	free(sub);
	return (rtv);
}

void	check_inside_sphere(t_scene *scene)
{
	t_object	*obj;
	t_list		*objects;
	t_sphere	*sp;

	objects = scene->objects;
	while (objects != NULL)
	{
		obj = objects->content;
		if (obj->type == T_SPHERE)
		{
			sp = obj->ptr;
			if (calc_dist(sp->center, scene->camera->point) < sp->diameter)
				puterr_exit("camera must be outside of sphere");
			if (calc_dist(sp->center, scene->light->point) < sp->diameter)
				puterr_exit("camera must be outside of sphere");
		}
		objects = objects->next;
	}
}

void	after_read_check(t_scene *scene)
{
	if (scene->camera == NULL)
		puterr_exit("camera must be 1");
	if (scene->ambient_light == NULL)
		puterr_exit("ambient_light must be 1");
	if (scene->light == NULL)
		puterr_exit("light must be 1");
	check_inside_sphere(scene);
}

t_scene	*read_file(char **argv)
{
	t_scene	*scene;
	int		fd;
	int		read_bytes;
	char	*line[MAX_INPUT_LINE_LEN];

	scene = (t_scene *)ft_xcalloc(1, sizeof(t_scene));
	fd = xopen(argv[1], O_RDONLY, 0);
	while (1)
	{
		read_bytes = get_next_line(fd, line);
		if (read_bytes == -1)
			puterr_exit("hh");
		if (read_bytes == 0)
			break ;
		if ((*line)[read_bytes - 1] == '\n')
			(*line)[read_bytes - 1] = '\0';
		read_element(scene, *line);
		free(*line);
	}
	xclose(fd);
	after_read_check(scene);
	return (scene);
}
