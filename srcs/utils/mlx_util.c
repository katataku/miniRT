/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 10:54:43 by ahayashi          #+#    #+#             */
/*   Updated: 2022/05/24 13:50:50 by ahayashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	pixel_put_to_image(t_image *data, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = (y * data->bytes_per_line + x * (data->bits_per_pixel / 8));
	dst = data->data_addr + offset;
	*(unsigned int *)dst = color;
}

int	get_trgb(int color, int trgb_type)
{
	return ((color >> 8 * trgb_type) & 0xFF);
}

int	make_color_from_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

static int	min(int a, int b)
{
	if (a <= b)
		return (a);
	else
		return (b);
}

int	add_color(int a, int b)
{
	return (make_color_from_trgb(\
			min(get_trgb(a, TRANSPARENT) + get_trgb(b, TRANSPARENT), 0xFF), \
			min(get_trgb(a, RED) + get_trgb(b, RED), 0xFF), \
			min(get_trgb(a, GREEN) + get_trgb(b, GREEN), 0xFF), \
			min(get_trgb(a, BLUE) + get_trgb(b, BLUE), 0xFF) \
			));
}

int	close_windows(t_scene *scene)
{
	(void)scene;
	exit(0);
}

int	deal_key(int key_code, t_scene *scene)
{
	if (key_code == KEY_ESC)
		close_windows(scene);
	return (0);
}

void	register_hooks(t_window_info *info, t_scene *scene)
{
	mlx_hook(info->win, X_EVENT_KEY_PRESS, 1, &deal_key, scene);
	mlx_hook(info->win, X_EVENT_KEY_EXIT, 1, &close_windows, scene);
	mlx_loop(info->mlx);
}
