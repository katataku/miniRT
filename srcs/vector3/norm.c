/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:18:26 by ahayashi          #+#    #+#             */
/*   Updated: 2022/05/16 14:18:26 by ahayashi         ###   ########.jp       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"

double	vec3_norm(t_vec3 *v)
{
	return (v->x * v->x + v->y * v->y + v->z * v->z);
}
