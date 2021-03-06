/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 17:00:28 by ahayashi          #+#    #+#             */
/*   Updated: 2022/04/02 22:52:02 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"

t_vec3	*vec3_sub(t_vec3	*left, t_vec3	*right)
{
	t_vec3	*rtv;

	rtv = (t_vec3 *)ft_xcalloc(1, sizeof(t_vec3));
	rtv->x = left->x - right->x;
	rtv->y = left->y - right->y;
	rtv->z = left->z - right->z;
	return (rtv);
}
