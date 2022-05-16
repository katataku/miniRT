/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 10:54:43 by ahayashi          #+#    #+#             */
/*   Updated: 2022/05/16 10:54:43 by ahayashi         ###   ########.jp       */
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

/*
 * TODO: 各バイトごとのオーバーフローを考慮。
 */
int	add_color(int a, int b)
{
	return(make_color_from_trgb( \
			get_trgb(a, TRANSPARENT) + get_trgb(b, TRANSPARENT), \
			get_trgb(a, RED) + get_trgb(b, RED), \
			get_trgb(a, GREEN) + get_trgb(b, GREEN), \
			get_trgb(a, BLUE) + get_trgb(b, BLUE) \
			));
}
