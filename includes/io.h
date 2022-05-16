/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 16:57:50 by takkatao          #+#    #+#             */
/*   Updated: 2022/05/16 17:15:00 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IO_H
# define IO_H

# include "define.h"
# include "utils.h"
# include "xsyscall.h"

t_scene	*read_file(char **argv);
void	validate_arg(int argc);

#endif
