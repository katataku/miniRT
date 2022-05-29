/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:26:14 by ahayashi          #+#    #+#             */
/*   Updated: 2022/05/29 16:12:51 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * カメラから見る方向への、正規化されたrayを計算する
 * カメラの位置(lookfrom)は入力ファイルのview_pointから設定。
 * カメラの見る向きは入力ファイルのorientation_vecの向きに設定。
 */
t_vec3	*calc_camera_ray(t_scene *scene)
{
	t_vec3	*lookat;
	t_vec3	*lookfrom;
	t_vec3	*camera_ray;
	t_vec3	*camera_ray_norm;

	lookfrom = scene->camera->point;
	lookat = vec3_add(lookfrom, scene->camera->orientation_vec);
	camera_ray = vec3_sub(lookat, lookfrom);
	camera_ray_norm = vec3_normalize(camera_ray);
	free(lookat);
	free(camera_ray);
	return (camera_ray_norm);
}

/*
 * vupを計算する。vupはカメラの上方向のベクトル。
 * カメラはz軸の正方向を上にしているとする。
 * カメラの視線ベクトルとvupが並行になってしまうと外積が0になってしまうため、少し角度をつける。
 */
t_vec3	*calc_vup(t_vec3 *camera_ray)
{
	double	sum;

	if (camera_ray->x == 0 && camera_ray->y == 0)
	{
		sum = sqrt(pow(0.1, 2) + 1);
		return (vector3(0, 0.1 / sum, 1 / sum));
	}
	return (vector3(0, 0, 1));
}

t_vec3	*calc_u_base(t_vec3	*camera_ray)
{
	t_vec3	*u_base;
	t_vec3	*vup;
	t_vec3	*tmp1;

	vup = calc_vup(camera_ray);
	tmp1 = vec3_outer_product(vup, camera_ray);
	u_base = vec3_normalize(tmp1);
	free(vup);
	free(tmp1);
	return (u_base);
}

t_vec3	*calc_u(t_scene *scene, t_vec3	*camera_ray, double x)
{
	t_vec3	*u;
	t_vec3	*u_base;
	double	screen_width;

	screen_width = tan(M_PI * scene->camera->fov / 180);
	u_base = calc_u_base(camera_ray);
	u = vec3_multiply(u_base, screen_width - 2 * screen_width * x / W);
	free(u_base);
	return (u);
}

t_vec3	*calc_v(t_scene *scene, t_vec3	*camera_ray, double y)
{
	t_vec3	*v;
	t_vec3	*v_base;
	t_vec3	*u_base;
	t_vec3	*tmp1;
	double	screen_width;

	screen_width = tan(M_PI * scene->camera->fov / 180);
	u_base = calc_u_base(camera_ray);
	tmp1 = vec3_outer_product(u_base, camera_ray);
	v_base = vec3_normalize(tmp1);
	v = vec3_multiply(v_base, -1 * screen_width + 2 * screen_width * y / H);
	free(tmp1);
	free(u_base);
	free(v_base);
	return (v);
}

/*
 * スクリーン座標をワールド座標に変換。
 * minilibXのpixelを3次元上のスクリーンに変換。
 * カメラからスクリーンの距離は1で固定。
 * u,vはスクリーン上での基底ベクトル。基底ベクトルはvupと直交するように設定する。
 */
t_vec3	*to_3d(t_scene *scene, double x, double y)
{
	t_vec3	*vec;
	t_vec3	*camera_ray;
	t_vec3	*u;
	t_vec3	*v;

	camera_ray = calc_camera_ray(scene);
	u = calc_u(scene, camera_ray, x);
	v = calc_v(scene, camera_ray, y);
	vec = vec3_add4(scene->camera->point, camera_ray, u, v);
	free(camera_ray);
	free(u);
	free(v);
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

t_object	*find_nearest_objects(t_ray *ray, t_list *objects, t_object *ignore_object)
{
	t_object	*rtv;
	double		t;
	double		min;

	min = DBL_MAX;
	rtv = NULL;
	while (objects != NULL)
	{
		if (ignore_object != objects->content)
		{
			t = calc_t(ray, objects->content);
			if (t > 0 && t < min)
			{
				rtv = objects->content;
				min = t;
			}
		}
		objects = objects->next;
	}
	return (rtv);
}

bool	is_draw_shadow(t_ray *camera_ray, t_object *object, t_light *light, t_list *objects)
{
	double		t;
	t_vec3		*p_vec;
	t_vec3		*d_vec;
	t_ray		shadow_ray;
	t_object	*nearest_object;

	t = calc_t(camera_ray, object);
	d_vec = vec3_multiply(camera_ray->direction_vec, t);
	p_vec = vec3_add(camera_ray->start_vec, d_vec);
	shadow_ray.start_vec = p_vec;
	shadow_ray.direction_vec = vec3_sub(light->point, p_vec);
	free(d_vec);
	nearest_object = find_nearest_objects(&shadow_ray, objects, object);
	free(p_vec);
	free(shadow_ray.direction_vec);
	if (nearest_object == NULL)
		return (false);
	return (true);
}

void	draw(t_window_info *info, t_scene *scene)
{
	int			i;
	int			j;
	t_ray		ray;
	t_object	*object;
	t_vec3		*vec_3d;

	ray.start_vec = scene->camera->point;
	i = 0;
	while (i < W)
	{
		j = 0;
		while (j < H)
		{
			vec_3d = to_3d(scene, i, j);
			ray.direction_vec = vec3_sub(vec_3d, ray.start_vec);
			object = find_nearest_objects(&ray, scene->objects, NULL);
			if (object != NULL && is_draw_shadow(&ray, object, scene->light, scene->objects) == false)
			{
				pixel_put_to_image(info->img, i, j, add_color(calc_diffuse_light(&ray, object, scene->light), calc_ambient_light(scene->ambient_lightning, object)));
			}
			free(vec_3d);
			free(ray.direction_vec);
			j++;
		}
		i++;
	}
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

int	main_loop(t_window_info *info)
{
	mlx_put_image_to_window(info->mlx, info->win, info->img->mlx_img, 0, 0);
	return (0);
}

void	register_hooks(t_window_info *info, t_scene *scene)
{
	mlx_hook(info->win, X_EVENT_KEY_PRESS, 1, &deal_key, scene);
	mlx_hook(info->win, X_EVENT_KEY_EXIT, 1, &close_windows, scene);
	mlx_loop_hook(info->mlx, &main_loop, info);
	mlx_loop(info->mlx);
}

int	main(int argc, char **argv)
{
	t_window_info	*info;
	t_scene			*scene;

	validate_arg(argc);
	info = init_window_info();
	scene = read_file(argv);
	draw(info, scene);
	register_hooks(info, scene);
	return (0);
}
