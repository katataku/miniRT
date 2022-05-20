/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:26:14 by ahayashi          #+#    #+#             */
/*   Updated: 2022/05/17 10:44:39 by ahayashi         ###   ########.jp       */
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

/*
 * 𝑡 =(−𝐵±√(𝐵^2−4𝐴𝐶))/2𝐴
 *
 * 𝐴 = |𝐝⃗|^2
 * 𝐵 = 2(𝐬⃗⋅𝐝⃗)
 * 𝐶 = |𝐬⃗|^2−𝑟^2
 * ※球が原点にあるとき。球の中心が原点に重なるように平行移動してあげれば良いので
 * カメラの位置ベクトルから球の中心の位置ベクトルを引いたものを𝐬⃗とする
 *
 * 判別式が0のとき、1つのする
 * 判別式が0より大きい時、2点で交わる。tが小さい方が手前になる。
 * 交わらない場合は決め打ちでtを-1にする。tがマイナスということは視点の後ろにある。
 */
double	calc_t(t_ray *ray, t_sphere	*sphere)
{
	double	a;
	double	b;
	double	c;
	double	dif;
	t_vec3	*s;

	s = vec3_sub(ray->start_vector, sphere->sphere_center);
	a = pow(vec3_norm(ray->direction_vector), 2);
	b = 2 * vec3_inner_product(s, ray->direction_vector);
	c = pow(vec3_norm(s), 2) - pow(sphere->diameter / 2, 2);
	dif = pow(b, 2) - 4 * a * c;
	if (dif < 0)
		return (-1);
	return (-b - sqrt(dif) / (2 * a));
}

/*
 * 環境光を計算する。
 */
int	calc_ambient_light(t_ambient_lightning *a)
{
	return (make_color_from_trgb(\
		get_trgb(a->color, TRANSPARENT), \
		get_trgb(a->color, RED) * a->lighting_ratio, \
		get_trgb(a->color, GREEN) * a->lighting_ratio, \
		get_trgb(a->color, BLUE) * a->lighting_ratio \
	));
}

/*
 * 拡散反射光を計算する。
 */
int	calc_diffuse_light(t_ray *ray, t_sphere *sphere, t_light *light)
{
	double	t;
	double	cos;
	t_vec3	*p_vec;
	t_vec3	*n_vec;
	t_vec3	*l_vec;

	t = calc_t(ray, sphere);
	p_vec = vec3_add(ray->start_vector, vec3_multiply(ray->direction_vector, t));
	n_vec = vec3_sub(p_vec, sphere->sphere_center);
	l_vec = vec3_sub(p_vec, light->light_point);
	cos = cos_of_angles(n_vec, l_vec);
	return (make_color_from_trgb(255, 0 * cos, 255 * cos, 255 * cos));
}

/*
 * レイと球が交差するか判定する関数。
 *
 * 判別式が0のとき、1つのする
 * 判別式が0より大きい時、2点で交わる。tが小さい方が手前になる。
 */
bool	is_cross(t_ray *ray, t_sphere *sphere)
{
	return (calc_t(ray, sphere) >= 0);
}

void	draw_sphere(t_window_info *info, t_scene *scene)
{
	int			i;
	int			j;
	t_ray		ray;

	ray.start_vector = scene->camera->view_point;
	i = 0;
	while (i < W)
	{
		j = 0;
		while (j < H)
		{
			ray.direction_vector = vec3_sub(to_3d(i, j), ray.start_vector);
			if (is_cross(&ray, scene->sphere))
			{
				pixel_put_to_image(info->img, i, j, add_color(calc_diffuse_light(&ray, scene->sphere, scene->light), calc_ambient_light(scene->ambient_lightning)));
			}
			j++;
		}
		i++;
	}
}

double	calc_t_plane(t_ray *ray, t_plane *plane)
{
	(void)ray;
	(void)plane;
	return (0);
}

/*
 *
 */
bool	is_cross_plane(t_ray *ray, t_plane *plane)
{
	return (calc_t_plane(ray, plane) >= 0);
}

/*
 * 拡散反射光を計算する。
 */
int	calc_diffuse_light_plane(t_ray *ray, t_plane *plane, t_light *light)
{
	(void)ray;
	(void)plane;
	(void)light;
	return (make_color_from_trgb(255, 0, 0, 0));
}

void	draw_plane(t_window_info *info, t_scene *scene)
{
	int			i;
	int			j;
	t_ray		ray;

	ray.start_vector = scene->camera->view_point;
	i = 0;
	while (i < W)
	{
		j = 0;
		while (j < H)
		{
			ray.direction_vector = vec3_sub(to_3d(i, j), ray.start_vector);
			if (is_cross_plane(&ray, scene->plane))
			{
				pixel_put_to_image(info->img, i, j, add_color(calc_diffuse_light_plane(&ray, scene->plane, scene->light), calc_ambient_light(scene->ambient_lightning)));
			}
			j++;
		}
		i++;
	}
}

void	draw(t_window_info *info, t_scene *scene)
{
	draw_plane(info, scene);
}

int	main(int argc, char **argv)
{
	t_window_info	*info;
	t_scene			*scene;

	validate_arg(argc);
	info = init_window_info();
	scene = read_file(argv);
	draw(info, scene);
	mlx_put_image_to_window(info->mlx, info->win, info->img->mlx_img, 0, 0);
	mlx_loop(info->mlx);
	return (0);
}
