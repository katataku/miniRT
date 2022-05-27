/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 22:15:57 by ahayashi          #+#    #+#             */
/*   Updated: 2022/05/27 17:39:53 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stdlib.h"

double	ft_atod(const char *str)
{
	char	*dot_pos;
	double	integer;
	double	decimal;

	integer = ft_atol(str);
	decimal = 0;
	dot_pos = ft_strchr(str, '.');
	if (dot_pos != NULL)
	{
		decimal = ft_atol(dot_pos + 1);
		while (decimal > 1)
			decimal /= 10;
		if (integer < 0)
			decimal *= -1;
	}
	return (integer + decimal);
}
