/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_dist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:03:51 by takkatao          #+#    #+#             */
/*   Updated: 2022/06/04 22:09:22 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector3.h"

double	calc_dist(t_vec3 *a, t_vec3 *b)
{
	t_vec3	*sub;
	double	rtv;

	sub = vec3_sub(a, b);
	rtv = vec3_norm(sub);
	free(sub);
	return (rtv);
}
