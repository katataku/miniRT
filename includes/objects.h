/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:29:44 by ahayashi          #+#    #+#             */
/*   Updated: 2022/06/04 22:12:20 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "mlx.h"
# include "xlibft.h"
# include "define.h"
# include "utils.h"

t_vec3			*calc_camera_ray(t_scene *scene);
t_vec3			*to_screen_vec(t_scene *scene, double x, double y);

//sphere
double			calc_t_sphere(t_ray *ray, t_sphere	*sphere);
double			calc_lambert_cos_sphere(t_ray *ray, t_sphere *s, t_light *l);

//plane
double			calc_t_plane(t_ray *ray, t_plane *plane);
double			calc_lambert_cos_plane(t_ray *ray, t_plane *p, t_light *light);

//cylinder
double			calc_lambert_cos_cylinder(t_ray *r, t_cylinder *c, t_light *l);
double			calc_t_cylinder(t_ray *ray, t_cylinder	*cylinder);
double			calc_height(t_vec3 *p_vec, t_cylinder	*cylinder);
t_vec3			*create_p_vec(t_vec3 *s, t_vec3 *d, double t);
t_vec3			*calc_p_cylinder(t_ray *ray, t_cylinder	*cylinder);
enum e_t_type	calc_t_type(t_ray *ray, t_cylinder	*cylinder);
double			decide_t(double t1, double t2, t_ray *ray, t_cylinder *cy);
enum e_t_type	decide_t_type(double t1, double t2, t_ray *ray, t_cylinder *cy);

//object
double			calc_t(t_ray *ray, t_object *object);
int				calc_ambient_light(t_ambient_light *a, t_object *object);
int				calc_diffuse_light(t_ray *ray, t_object *o, t_light *light);

int				calc_pixel_color(int x, int y, t_scene *sc);
#endif
