/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:15:28 by ahayashi          #+#    #+#             */
/*   Updated: 2022/05/24 14:17:32 by ahayashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

bool	is_cross(t_ray *ray, t_object *object)
{
	if (object->identifier == T_PLANE)
		return (is_cross_plane(ray, object));
	else if (object->identifier == T_SPHERE)
		return (is_cross_sphere(ray, object));
	return (false);
}

int	calc_diffuse_light(t_ray *ray, t_object *object, t_light *light)
{
	(void)ray;
	(void)object;
	(void)light;
	return (0);
}
