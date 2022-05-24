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

double	calc_t(t_ray *ray, t_object *object)
{
	if (object->type == T_PLANE)
		return (calc_t_plane(ray, object->ptr));
	else if (object->type == T_SPHERE)
		return (calc_t_sphere(ray, object->ptr));
	return (-1);
}
