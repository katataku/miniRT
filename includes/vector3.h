/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:58:08 by ahayashi          #+#    #+#             */
/*   Updated: 2022/04/02 23:39:40 by takkatao         ###   ########.fr       */
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

#endif
