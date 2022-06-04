/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 09:04:25 by takkatao          #+#    #+#             */
/*   Updated: 2022/06/03 09:12:51 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"

double	ft_atod(const char *str)
{
	char	*dot_pos;
	double	integer;
	double	decimal;
	int		decimal_len;
	double	sign;

	if (str[0] == '-')
		sign = -1;
	else
		sign = 1;
	integer = ft_abs(ft_atol(str));
	decimal = 0;
	dot_pos = ft_strchr(str, '.');
	if (dot_pos != NULL)
	{
		decimal_len = ft_strlen(dot_pos + 1);
		decimal = ft_atol(dot_pos + 1);
		while (decimal_len-- > 0)
			decimal /= 10;
		if (integer < 0)
			decimal *= -1;
	}
	return (sign * (integer + decimal));
}
