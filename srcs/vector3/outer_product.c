/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outer_product.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 10:47:22 by ahayashi          #+#    #+#             */
/*   Updated: 2022/05/23 00:17:24 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"

t_vec3	*vec3_outer_product(t_vec3 *left, t_vec3 *right)
{
	return (vector3(\
		left->y * right->z - left->z * right->y, \
		left->z * right->x - left->x * right->z, \
		left->x * right->y - left->y * right->x));
}
