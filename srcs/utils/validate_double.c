/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_double.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 15:26:32 by takkatao          #+#    #+#             */
/*   Updated: 2022/06/04 16:25:37 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

double	atod_with_validation(char *value, char *message, double min, double max)
{
	double	number;
	bool	is_valid;
	char	*dot_pos;
	char	*cpy_str;

	is_valid = true;
	cpy_str = ft_xstrdup(value);
	dot_pos = ft_strchr(cpy_str, '.');
	*dot_pos = '\0';
	atoi_with_validation(cpy_str, "number length too long", -999999, 999999);
	atoi_with_validation(dot_pos + 1, "number length too long", \
		-999999, 999999);
	number = ft_atod(value);
	if (number < min || number > max)
		is_valid = false;
	if (!is_valid)
		puterr_exit(message);
	return (number);
}

double	atod_ratio(char *str)
{
	return (atod_with_validation(str, "ratio must be [0.0, 1.0]", 0.0, 1.0));
}

double	atod_orientation_vector(char *str)
{
	return (atod_with_validation(str, \
		"orientation vector must be [-1.0, 1.0]", -1.0, 1.0));
}

double	atod_validatiton_wrapper(char *str)
{
	return (atod_with_validation(str, \
		"vector must be [-999999.999999, 999999.999999]", -999999.999999, 999999.999999));
}
