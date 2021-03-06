/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 14:18:26 by ahayashi          #+#    #+#             */
/*   Updated: 2022/05/23 16:05:50 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"

t_vec3	*vec3_normalize(t_vec3 *vec)
{
	return (vec3_multiply(vec, 1 / vec3_norm(vec)));
}
