/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:58:08 by ahayashi          #+#    #+#             */
/*   Updated: 2022/04/03 00:39:07 by ahayashi         ###   ########.jp       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR3_H
# define VECTOR3_H

# include "xlibft.h"

typedef struct s_vector3 {
	double	x;
	double	y;
	double	z;
}	t_vec3;

t_vec3	*add(t_vec3	*left, t_vec3	*right);
t_vec3	*sub(t_vec3	*left, t_vec3	*right);
double	vec3_inner_product(t_vec3 *left, t_vec3 *right);
void	print(t_vec3 *vector);
t_vec3	*vector3(double x, double y, double z);

#endif
