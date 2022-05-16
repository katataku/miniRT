/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:02:57 by ahayashi          #+#    #+#             */
/*   Updated: 2022/05/16 10:57:10 by ahayashi         ###   ########.jp       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "define.h"
# include "libft.h"
# include "xlibft.h"

void	puterr(char *target, char *message);
void	puterr_exit(char *target, char *message, int exit_status);
char	*triple_join(char *s1, char *s2, char *s3);
void	pixel_put_to_image(t_image *data, int x, int y, int color);

#endif
