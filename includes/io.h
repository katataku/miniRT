/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:57:50 by takkatao          #+#    #+#             */
/*   Updated: 2022/06/04 17:51:07 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# include <string.h>
# include "define.h"
# include "utils.h"
# include "xsyscall.h"

t_scene		*read_file(char **argv);
void		validate_arg(int argc, char **argv);
int			get_color_from_line(char *color_line);
t_vec3		*gen_pos_vec3_from_line(char *vec_line);
t_vec3		*gen_orientation_vec3_from_line(char *vec_line);
void		read_ambient(t_scene *scene, char **splitted_line);
void		read_camera(t_scene *scene, char **splitted_line);
void		read_light(t_scene *scene, char **splitted_line);
t_object	*read_sphere(char	**splitted_line);
t_object	*read_plane(char	**splitted_line);
t_object	*read_cylinder(char	**splitted_line);
int			count_splits(char **str);

#endif
