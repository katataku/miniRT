/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:02:57 by ahayashi          #+#    #+#             */
/*   Updated: 2022/06/04 16:24:32 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "define.h"
# include "libft.h"
# include "xlibft.h"

enum e_trgb
{
	BLUE,
	GREEN,
	RED,
	TRANSPARENT
};

void	puterr(char *message);
void	puterr_exit(char *message);
char	*triple_join(char *s1, char *s2, char *s3);
void	pixel_put_to_image(t_image *data, int x, int y, int color);
int		get_trgb(int color, int trgb_type);
int		make_color_from_trgb(int t, int r, int g, int b);
int		add_color(int a, int b);
int		atoi_color(char *str);
int		atoi_fov(char *fov);
double	ft_atod(const char *str);
int		atoi_with_validation(char *value, char *message, int min, int max);
double	atod_validatiton_wrapper(char *str);
double	atod_ratio(char *str);
double	atod_orientation_vector(char *str);
int		atoi_color(char *str);
int		atoi_fov(char *str);

#endif
