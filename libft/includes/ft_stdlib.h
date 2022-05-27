/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stdlib.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 18:04:44 by ahayashi          #+#    #+#             */
/*   Updated: 2022/05/27 17:41:03 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STDLIB_H
# define FT_STDLIB_H

# include "ft_ctype.h"
# include "ft_string.h"
# include <errno.h>
# include <limits.h>
# include <stdlib.h>

int		ft_abs(int n);
double	ft_atod(const char *str);
int		ft_atoi(const char *str);
long	ft_atol(const char *str);
void	*ft_calloc(size_t count, size_t size);
int		ft_is_integer(char *str);
int		ft_is_long_value(char *str);
int		ft_is_number(char *str);
char	*ft_itoa(int n);

#endif
