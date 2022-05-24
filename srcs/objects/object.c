/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:15:28 by ahayashi          #+#    #+#             */
/*   Updated: 2022/05/24 16:27:41 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

bool	is_cross(t_ray *ray, t_object *object)
{
	if (object->type == T_PLANE)
		return (is_cross_plane(ray, object->ptr));
	else if (object->type == T_SPHERE)
		return (is_cross_sphere(ray, object->ptr));
	return (false);
}

int	calc_diffuse_light(t_ray *ray, t_object *object, t_light *light)
{
	if (object->type == T_PLANE)
		return (calc_diffuse_light_plane(ray, object->ptr, light));
	else if (object->type == T_SPHERE)
		return (calc_diffuse_light_sphere(ray, object->ptr, light));
	return (0);
}

int	calc_ambient_light(t_ambient_light *a, t_object *object)
{
	int	color;

	if (object->type == T_PLANE)
		color = ((t_plane *)(object->ptr))->color;
	else if (object->type == T_SPHERE)
		color = ((t_sphere *)(object->ptr))->color;
	else
		color = 0;
	return (make_color_from_trgb(\
		0xFF, \
		get_trgb(a->color, RED) * a->ratio * get_trgb(color, RED) / 255, \
		get_trgb(a->color, GREEN) * a->ratio * get_trgb(color, GREEN) / 255, \
		get_trgb(a->color, BLUE) * a->ratio * get_trgb(color, BLUE) / 255 \
	));
}

double	calc_t(t_ray *ray, t_object *object)
{
	if (object->type == T_PLANE)
		return (calc_t_plane(ray, object->ptr));
	else if (object->type == T_SPHERE)
		return (calc_t_sphere(ray, object->ptr));
	return (-1);
}
