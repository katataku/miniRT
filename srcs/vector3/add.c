/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 17:00:28 by ahayashi          #+#    #+#             */
/*   Updated: 2022/04/02 17:21:50 by ahayashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"

t_vector3	*add(t_vector3	*left, t_vector3	*right)
{
	t_vector3	*rtv;

	rtv = (t_vector3 *)ft_xcalloc(1, sizeof(t_vector3));
	rtv->x = left->x + right->x;
	rtv->y = left->y + right->y;
	rtv->z = left->z + right->z;
	return (rtv);
}
