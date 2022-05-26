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

static int	calc_color(int color, double ratio, int reflection)
{
	return (make_color_from_trgb(\
		0xFF, \
		get_trgb(color, RED) * ratio * get_trgb(reflection, RED) / 255, \
		get_trgb(color, GREEN) * ratio * get_trgb(reflection, GREEN) / 255, \
		get_trgb(color, BLUE) * ratio * get_trgb(reflection, BLUE) / 255 \
	));
}

int	calc_diffuse_light(t_ray *ray, t_object *object, t_light *light)
{
	double	cos;
	double	reflection;

	if (object->type == T_PLANE)
	{
		cos = calc_lambert_cos_plane(ray, object->ptr, light);
		reflection = ((t_plane *)(object->ptr))->color;
	}
	else
	{
		cos = calc_lambert_cos_sphere(ray, object->ptr, light);
		reflection = ((t_sphere *)(object->ptr))->color;
	}
	return (calc_color(light->color, light->ratio * cos, reflection));
}

int	calc_ambient_light(t_ambient_light *a, t_object *object)
{
	int	reflection;

	if (object->type == T_PLANE)
		reflection = ((t_plane *)(object->ptr))->color;
	else if (object->type == T_SPHERE)
		reflection = ((t_sphere *)(object->ptr))->color;
	else
		reflection = 0;
	return (calc_color(a->color, a->ratio, reflection));
}

double	calc_t(t_ray *ray, t_object *object)
{
	if (object->type == T_PLANE)
		return (calc_t_plane(ray, object->ptr));
	else if (object->type == T_SPHERE)
		return (calc_t_sphere(ray, object->ptr));
	return (-1);
}
