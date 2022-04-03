/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 17:00:28 by ahayashi          #+#    #+#             */
/*   Updated: 2022/04/02 23:57:03 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"

t_vec3	*vector3(double x, double y, double z)
{
	t_vec3	*rtv;

	rtv = (t_vec3 *)ft_xcalloc(1, sizeof(t_vec3));
	rtv->x = x;
	rtv->y = y;
	rtv->z = z;
	return (rtv);
}
