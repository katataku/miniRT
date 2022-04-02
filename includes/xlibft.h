/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xlibft.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 23:39:45 by ahayashi          #+#    #+#             */
/*   Updated: 2022/02/25 14:08:33 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XLIBFT_H
# define XLIBFT_H

# include "libft.h"
# include "define.h"

char	*ft_xcalloc(size_t count, size_t size);
t_list	*ft_xlstnew(void *content);
char	**ft_xsplit(const char *s, char c);
char	*ft_xstrdup(const char *s);
char	*ft_xstrjoin(const char *s1, const char *s2);
#endif
