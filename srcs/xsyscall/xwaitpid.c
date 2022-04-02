/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xwaitpid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:28:29 by ahayashi          #+#    #+#             */
/*   Updated: 2022/04/02 16:28:30 by ahayashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xsyscall.h"

pid_t	xwaitpid(pid_t pid, int *stat_loc, int options)
{
	pid_t	ret;

	ret = waitpid(pid, stat_loc, options);
	if (ret == -1)
	{
		perror("waitpid");
		exit(1);
	}
	return (ret);
}
