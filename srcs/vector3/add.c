/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 17:00:28 by ahayashi          #+#    #+#             */
/*   Updated: 2022/05/27 16:20:53 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"

t_vec3	*vec3_add(t_vec3	*left, t_vec3	*right)
{
	t_vec3	*rtv;

	rtv = (t_vec3 *)ft_xcalloc(1, sizeof(t_vec3));
	rtv->x = left->x + right->x;
	rtv->y = left->y + right->y;
	rtv->z = left->z + right->z;
	return (rtv);
}

t_vec3	*vec3_add4(t_vec3	*v1, t_vec3	*v2, t_vec3	*v3, t_vec3	*v4)
{
	t_vec3	*tmp1;
	t_vec3	*tmp2;
	t_vec3	*rtv;

	tmp1 = vec3_add(v1, v2);
	tmp2 = vec3_add(v3, v4);
	rtv = vec3_add(tmp1, tmp2);
	free(tmp1);
	free(tmp2);
	return (rtv);
}
