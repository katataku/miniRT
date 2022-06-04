/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_integer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 15:26:32 by takkatao          #+#    #+#             */
/*   Updated: 2022/06/04 17:48:24 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	atoi_with_validation(char *value, char *message, int min, int max)
{
	int		number;
	bool	is_valid;

	is_valid = true;
	if (!ft_is_number(value))
		is_valid = false;
	if (!ft_is_integer(value))
		is_valid = false;
	if (errno == ERANGE)
		is_valid = false;
	number = ft_atoi(value);
	if (number < min || number > max)
		is_valid = false;
	if (!is_valid)
		puterr_exit(message);
	return (number);
}

int	atoi_color(char *str)
{
	int	color;

	color = atoi_with_validation(str, "color must be 0-255 in int", 0, 255);
	return (color);
}

int	atoi_fov(char *str)
{
	int	fov;

	fov = atoi_with_validation(str, "fov must be 0-180 in int", 0, 180);
	return (fov);
}
