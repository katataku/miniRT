/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:57:50 by takkatao          #+#    #+#             */
/*   Updated: 2022/05/17 16:39:32 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# include "define.h"
# include "utils.h"
# include "xsyscall.h"

t_scene	*read_file(char **argv);
void	validate_arg(int argc);
int		get_color_from_line(char *color_line);
t_vec3	*gen_vec3_from_line(char *vec_line);
void	read_ambient(t_scene *scene, char **splitted_line);
void	read_camera(t_scene *scene, char **splitted_line);
void	read_light(t_scene *scene, char **splitted_line);
void	read_sphere(t_scene *scene, char **splitted_line);
void	read_plane(t_scene *scene, char **splitted_line);
void	read_cylinder(t_scene *scene, char **splitted_line);

#endif
