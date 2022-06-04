/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:04:02 by ahayashi          #+#    #+#             */
/*   Updated: 2022/06/04 15:30:49 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	puterr(char *message)
{
	if (ft_putstr_fd("Error\n", STDERR_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (ft_putendl_fd(message, STDERR_FILENO) == -1)
		exit(EXIT_FAILURE);
}

void	puterr_exit(char *message)
{
	puterr(message);
	exit(EXIT_FAILURE);
}
