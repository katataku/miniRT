/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:26:14 by ahayashi          #+#    #+#             */
/*   Updated: 2022/05/16 10:54:59 by ahayashi         ###   ########.jp       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * スクリーン座標をワールド座標に変換。
 * minilibXのpixelを3次元上のスクリーンに変換。
 * 固定値の意味なんだっけ。
 */
t_vec3	*to_3d(double x, double y)
{
	t_vec3	*vec;

	vec = (t_vec3 *)malloc(sizeof(t_vec3));
	vec->x = -1 + 2 * x / W;
	vec->y = 1 - 2 * y / H;
	vec->z = 9;
	return (vec);
}

/*
 * return -1, if t is not calculated.
 */
double	calc_t(t_vec3 *s, t_vec3 *d)
{
	double	a;
	double	b;
	double	c;
	double	r;
	double	dif;
	double	t;


	r = 2;
	a = pow(d->x, 2) + pow(d->y, 2) + pow(d->z, 2);
	b = 2 * (s->x * d->x + s->y * d->y + s->z * d->z);
	c = pow(s->x, 2) + pow(s->y, 2) + pow(s->z, 2) - pow(r, 2);
	dif = pow(b, 2) - 4 * a * c;
	if (dif < 0)
		return (-1);
	t = - b - sqrt(dif) / (2 * a);
	return (t);
}

/*
 * 判別式が0のとき、1つのする
 * 判別式が0より大きい時、2点で交わる。tが小さい方が手前になる。
 */
bool	is_cross(t_vec3 *s, t_vec3 *d)
{
	return (calc_t(s, d) >= 0);
}

t_window_info	*init_window_info(void)
{
	t_window_info	*info;

	info = ft_calloc(1, sizeof(t_window_info));
	info->mlx = mlx_init();
	info->win = mlx_new_window(info->mlx, W, H, "minirt");
	info->img = malloc(sizeof(t_image));
	info->img->mlx_img = mlx_new_image(info->mlx, 1001, 1001);
	info->img->data_addr = mlx_get_data_addr(info->img->mlx_img, \
		&info->img->bits_per_pixel, &info->img->bytes_per_line, \
		&info->img->endian);
	return (info);
}

int	calc_ambient_light(void)
{
	t_ambient_lightning	a = {0.8, 0xFF00FFFF};

	return (make_color_from_trgb(
		get_trgb(a.color, TRANSPARENT), \
		get_trgb(a.color, RED) * a.lighting_ratio, \
		get_trgb(a.color, GREEN) * a.lighting_ratio, \
		get_trgb(a.color, BLUE) * a.lighting_ratio
	));
}

int	calc_diffuse_light(void)
{
	return (1);
}

// start_vecがカメラの座標。
void	draw(t_window_info *info)
{
	t_vec3		*d_vec;
	t_vec3		*start_vec;
	int			i;
	int			j;
	t_camera	camera = {
			{0.0, 0.0, 10.0},
			{0.0, 0.0, 0.0},
			0
	};
	t_sphere	sphere = {
			{3.0, 3.0, 0.0},
			4,
			0xFF00FFFF,
	};

	start_vec = vec3_sub(&sphere.sphere_center, &camera.view_point);

	i = 0;
	while (i < W)
	{
		j = 0;
		while (j < H)
		{
			d_vec = vec3_sub(&sphere.sphere_center, to_3d(i, j));
			if (is_cross(start_vec, vec3_sub(d_vec, start_vec)))
			{
				double	t = calc_t(start_vec, vec3_sub(d_vec, start_vec));
				t_vec3	*p_vec = vec3_add(&camera.view_point, vec3_multiply(d_vec, t));
				t_vec3	*n_vec = vec3_sub(p_vec, &sphere.sphere_center);

				t_vec3	*light_vec = vector3(0, 0, 0);
				t_vec3	*l_vec = vec3_sub(p_vec, light_vec);

				double cos = cos_of_angles(n_vec, l_vec);
//				int magic_nomber_to_adjast_visibility = 100;
//				cos *= magic_nomber_to_adjast_visibility;
				printf("%f\n",cos);
				pixel_put_to_image(info->img, i, j, make_color_from_trgb(255, 0*cos, 255*cos, 255 * cos));

//				pixel_put_to_image(info->img, i, j, calc_ambient_light());
			}
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
