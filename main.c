/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:26:14 by ahayashi          #+#    #+#             */
/*   Updated: 2022/04/03 00:56:05 by ahayashi         ###   ########.jp       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	pixel_put_to_image(t_image *data, int x, int y, int color)
{
	char	*dst;
	int		offset;

	offset = (y * data->bytes_per_line + x * (data->bits_per_pixel / 8));
	dst = data->data_addr + offset;
	*(unsigned int *)dst = color;
}

t_vec3	*to_3d(double x, double y)
{
	t_vec3	*vec;

	vec = (t_vec3 *)malloc(sizeof(t_vec3));
	vec->x = -1 + 2 * x / W;
	vec->y = 1 - 2 * y / H;
	vec->z = 9;
	return (vec);
}

bool	is_cross(t_vec3 *s, t_vec3 *d)
{
	double	a;
	double	b;
	double	c;
	double	dif;

	a = pow(d->x, 2) + pow(d->y, 2) + pow(d->z, 2);
	b = 2 * (s->x * d->x + s->y * d->y + s->z * d->z);
	c = pow(s->x, 2) + pow(s->y, 2) + pow(s->z, 2) - 1;
	dif = pow(b, 2) - 4 * a * c;
	return (dif >= 0);
}

t_window_info	*init_window_info(void)
{
	t_window_info	*info;

	info = ft_calloc(1, sizeof(t_window_info));
	info->mlx = mlx_init();
	info->win = mlx_new_window(info->mlx, 1001, 1001, "minirt");
	info->img = malloc(sizeof(t_image));
	info->img->mlx_img = mlx_new_image(info->mlx, 1001, 1001);
	info->img->data_addr = mlx_get_data_addr(info->img->mlx_img, \
		&info->img->bits_per_pixel, &info->img->bytes_per_line, \
		&info->img->endian);
	return (info);
}

void	draw(t_window_info *info)
{
	t_vec3	*vec;
	t_vec3	*start;
	int			i;
	int			j;

	i = 0;
	while (i < W)
	{
		j = 0;
		while (j < H)
		{
			vec = to_3d(i, j);
			start = vector3(0.0, 0.0, 10.0);
			if (is_cross(start, sub(vec, start)))
				pixel_put_to_image(info->img, i, j, 0xff00ffff);
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_window_info	*info;

	(void)argc;
	(void)argv;
	info = init_window_info();
	draw(info);
	mlx_put_image_to_window(info->mlx, info->win, info->img->mlx_img, 0, 0);
	mlx_loop(info->mlx);
	return (0);
}
