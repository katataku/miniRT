/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:58:08 by ahayashi          #+#    #+#             */
/*   Updated: 2022/05/16 11:01:51 by ahayashi         ###   ########.jp       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR3_H
# define VECTOR3_H

# include "xlibft.h"
# include <stdio.h>
# include <math.h>

typedef struct s_vector3 {
	double	x;
	double	y;
	double	z;
}	t_vec3;

t_vec3	*vec3_add(t_vec3	*left, t_vec3	*right);
t_vec3	*vec3_sub(t_vec3	*left, t_vec3	*right);
double	vec3_inner_product(t_vec3 *left, t_vec3 *right);
t_vec3	*vec3_multiply(t_vec3 *v, double scalar);
void	vec3_print(t_vec3 *vector);
double	vec3_norm(t_vec3 *v);
t_vec3	*vector3(double x, double y, double z);

#endif
