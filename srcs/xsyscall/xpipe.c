/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpipe.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:28:34 by ahayashi          #+#    #+#             */
/*   Updated: 2022/04/02 16:28:34 by ahayashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xsyscall.h"

int	xpipe(int fildes[2])
{
	int	status;

	status = pipe(fildes);
	if (status == -1)
	{
		perror("pipe");
		exit(1);
	}
	return (status);
}
