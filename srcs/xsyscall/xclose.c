/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xclose.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:28:40 by ahayashi          #+#    #+#             */
/*   Updated: 2022/04/02 16:28:41 by ahayashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xsyscall.h"

int	xclose(int fildes)
{
	int	status;

	status = close(fildes);
	if (status == -1)
	{
		perror("close");
		exit(1);
	}
	return (status);
}
