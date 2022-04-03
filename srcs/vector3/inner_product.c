/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inner_product.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 10:47:22 by ahayashi          #+#    #+#             */
/*   Updated: 2022/04/03 10:47:22 by ahayashi         ###   ########.jp       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"

double	vec3_inner_product(t_vec3 *left, t_vec3 *right)
{
	return (left->x * right->x + left->y * right->y + left->z * right->z);
}
