/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xdup2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:27:41 by ahayashi          #+#    #+#             */
/*   Updated: 2022/04/02 16:27:42 by ahayashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xsyscall.h"

int	xdup2(int fildes, int fildes2)
{
	int	status;

	status = dup2(fildes, fildes2);
	if (status == -1)
	{
		perror("dup2");
		exit(1);
	}
	return (status);
}
