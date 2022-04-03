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

t_vector3	*to_3d(double x, double y)
{
	t_vector3	*vec;

	vec = (t_vector3 *)malloc(sizeof(t_vector3));
	vec->x = -1 + 2 * x / W;
	vec->y = 1 - 2 * y / H;
	vec->z = 9;
	return (vec);
}

bool	is_cross(t_vector3 *s, t_vector3 *d)
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

int	main(int argc, char **argv, char **env)
{
	void		*mlx;
	void		*win;
	t_image		*img;
	t_vector3	*vec;
	t_vector3	*start;
	int			i;
	int			j;

	(void)argc;
	(void)argv;
	(void)env;
	mlx = mlx_init();
	win = mlx_new_window(mlx, 1001, 1001, "minirt");
	img = malloc(sizeof(t_image));
	img->mlx_img = mlx_new_image(mlx, 1001, 1001);
	img->data_addr = mlx_get_data_addr(img->mlx_img, \
		&img->bits_per_pixel, &img->bytes_per_line, \
		&img->endian);
	i = 0;
	while (i < W)
	{
		j = 0;
		while (j < H)
		{
			vec = to_3d(i, j);
			start = vector3(0.0, 0.0, 10.0);
			if (is_cross(start, sub(vec, start)))
				pixel_put_to_image(img, i, j, 0xff00ffff);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx, win, img->mlx_img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
