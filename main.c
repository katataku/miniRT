/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:26:14 by ahayashi          #+#    #+#             */
/*   Updated: 2022/05/14 18:30:34 by takkatao         ###   ########.fr       */
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


int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

int	get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int	get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int add_trgb(int a, int b)
{
	return(create_trgb(get_t(a) + get_t(b), \
					   get_r(a) + get_r(b), \
					   get_g(a) + get_g(b), \
					   get_b(a) + get_b(b)));
}


double norm(t_vec3 *a)
{
	return (a->x * a->x + a->y * a->y + a->z * a->z);
}

double subtended_angle_cos(t_vec3 *a, t_vec3 *b)
{

	return (vec3_inner_product(a, b) / (norm(a) * norm(b)));
}

int	calc_ambient_light(void)
{
	int	ambient_color = 0xFF00FFFF;
	double	ambient_ration= 0.8;

	return (create_trgb(
		get_t(ambient_color), \
		get_r(ambient_color) * ambient_ration, \
		get_g(ambient_color) * ambient_ration, \
		get_b(ambient_color) * ambient_ration
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
	t_vec3		*camera_vec;
	t_vec3		*start_vec;
	t_vec3		*object_vec;
	t_vec3		*ambient_vec;
	int			i;
	int			j;
	double		camera_x;
	double		camera_y;
	double		camera_z;
	double		object_x;
	double		object_y;
	double		object_z;

	object_x = 0.0;
	object_y = 0.0;
	object_z = 0.0;
	object_vec = vector3(object_x, object_y, object_z);

	camera_x = 0.0;
	camera_y = 0.0;
	camera_z = 10.0;
	camera_vec = vector3(camera_x, camera_y, camera_z);
	start_vec = sub(object_vec, camera_vec);

	i = 0;
	while (i < W)
	{
		j = 0;
		while (j < H)
		{
			d_vec = sub(object_vec, to_3d(i, j));
			if (is_cross(start_vec, sub(d_vec, start_vec)))
			{
				(void)ambient_vec;
				double	t = calc_t(start_vec, sub(d_vec, start_vec));
				t_vec3	*p_vec = add(camera_vec,  vec3_multiply(d_vec, t));
				t_vec3	*n_vec = sub(p_vec, object_vec);

				t_vec3	*light_vec = vector3(100, 10, 10);
				t_vec3	*l_vec = sub(p_vec, light_vec);

				double cos = subtended_angle_cos(n_vec, l_vec);
				int magic_nomber_to_adjast_visibility = 20000;
				cos *= magic_nomber_to_adjast_visibility;
				printf("%f\n",cos);
				pixel_put_to_image(info->img, i, j, create_trgb(255, 0*cos, 255*cos, 255 * cos));

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
