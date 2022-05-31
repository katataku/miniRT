/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:29:44 by ahayashi          #+#    #+#             */
/*   Updated: 2022/05/31 13:59:36 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "mlx.h"
# include "xlibft.h"
# include "define.h"
# include "utils.h"

//sphere
double	calc_t_sphere(t_ray *ray, t_sphere	*sphere);
double	calc_lambert_cos_sphere(t_ray *ray, t_sphere *sphere, t_light *light);

//plane
double	calc_t_plane(t_ray *ray, t_plane *plane);
double	calc_lambert_cos_plane(t_ray *ray, t_plane *plane, t_light *light);

//cylinder
double	calc_lambert_cos_cylinder(t_ray *ray, t_cylinder *cy, t_light *light);
double	calc_t_cylinder(t_ray *ray, t_cylinder	*cylinder);
double	calc_height(t_vec3 *p_vec, t_cylinder	*cylinder);
t_vec3	*create_p_vec(t_vec3 *s, t_vec3 *d, double t);


//object
double	calc_t(t_ray *ray, t_object *object);
int		calc_ambient_light(t_ambient_light *a, t_object *object);
int		calc_diffuse_light(t_ray *ray, t_object *object, t_light *light);

#endif
