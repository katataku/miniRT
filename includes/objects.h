/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:29:44 by ahayashi          #+#    #+#             */
/*   Updated: 2022/05/24 16:28:27 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "mlx.h"
# include "xlibft.h"
# include "define.h"
# include "utils.h"

//sphere

//plane
double	calc_t_plane(t_ray *ray, t_plane *plane);
bool	is_cross_plane(t_ray *ray, t_plane *plane);
int		calc_diffuse_light_plane(t_ray *ray, t_plane *plane, t_light *light);
void	draw_plane(t_window_info *info, t_scene *scene);
int		calc_diffuse_light_sphere(t_ray *ray, t_sphere *sphere, t_light *light);
bool	is_cross_sphere(t_ray *ray, t_sphere *sphere);
double	calc_t_sphere(t_ray *ray, t_sphere	*sphere);

//object
bool	is_cross(t_ray *ray, t_object *object);
int		calc_diffuse_light(t_ray *ray, t_object *object, t_light *light);
double	calc_t(t_ray *ray, t_object *object);

#endif
