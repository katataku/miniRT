/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 16:09:06 by ahayashi          #+#    #+#             */
/*   Updated: 2022/04/02 16:19:38 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * ^Cは表示されてしまう
 */
void	sigint_handler(int signal)
{
	(void)signal;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

/*
 * SIGQUITは特に何もしなくても無視されていそう　
 */
void	set_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
}

int	main(int argc, char **argv, char **env)
{
	char		*line;

	return (0);
}
