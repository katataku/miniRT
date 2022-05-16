/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cos_of_angles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:47:33 by ahayashi          #+#    #+#             */
/*   Updated: 2022/05/16 14:47:33 by ahayashi         ###   ########.jp       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"

double	cos_of_angles(t_vec3 *v1, t_vec3 *v2)
{
	return (vec3_inner_product(v1, v2) / (vec3_norm(v1) * vec3_norm(v2)));
}
