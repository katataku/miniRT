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
	float	x;
	float	y;
	float	z;
}	t_vector3;

t_vector3	*add(t_vector3	*left, t_vector3	*right);
t_vector3	*sub(t_vector3	*left, t_vector3	*right);
t_vector3	*vector3(double x, double y, double z);

#endif
