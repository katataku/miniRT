/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:02:57 by ahayashi          #+#    #+#             */
/*   Updated: 2022/05/24 13:52:16 by ahayashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "define.h"
# include "libft.h"
# include "xlibft.h"
# include "mlx.h"

enum e_trgb
{
	BLUE,
	GREEN,
	RED,
	TRANSPARENT
};

void	puterr(char *target, char *message);
void	puterr_exit(char *target, char *message, int exit_status);
char	*triple_join(char *s1, char *s2, char *s3);
void	pixel_put_to_image(t_image *data, int x, int y, int color);
int		get_trgb(int color, int trgb_type);
int		make_color_from_trgb(int t, int r, int g, int b);
int		add_color(int a, int b);
int		close_windows(t_scene *scene);
int		deal_key(int key_code, t_scene *scene);
void	register_hooks(t_window_info *info, t_scene *scene);

#endif
