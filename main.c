/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:26:14 by ahayashi          #+#    #+#             */
/*   Updated: 2022/05/26 20:16:02 by takkatao         ###   ########.fr       */
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
 * vupを計算する。
 * vupは(1, 0, 0)を基本とするが、
 * このベクトルとcamera_rayが並行な場合は他のベクトルをvupとする
 */
t_vec3	*calc_vup(t_vec3 *camera_ray)
{
	if (camera_ray->y == 0 && camera_ray->z == 0)
		return (vector3(0, 1, 0));
	return (vector3(1, 0, 0));
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
	double	screen_width;

	screen_width = tan(M_PI * scene->camera->fov / 180);
	camera_ray = calc_camera_ray(scene);
	u = vec3_normalize(vec3_outer_product(calc_vup(camera_ray), camera_ray));
	v = vec3_normalize(vec3_outer_product(u, camera_ray));
	vec = vec3_add(scene->camera->point, camera_ray);
	vec = vec3_add(vec, vec3_multiply(u, -1 * screen_width + 2 * screen_width * x / W));
	vec = vec3_add(vec, vec3_multiply(v, -1 * screen_width + 2 * screen_width * y / H));
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
	double	t;
	t_vec3	*p_vec;
	t_vec3	*d_vec;
	t_ray	shadow_ray;

	t = calc_t(camera_ray, object);
	d_vec = vec3_multiply(camera_ray->direction_vec, t);
	p_vec = vec3_add(camera_ray->start_vec, d_vec);
	shadow_ray.start_vec = p_vec;
	shadow_ray.direction_vec = vec3_sub(light->point, p_vec);
	free(d_vec);
	free(p_vec);
	free(shadow_ray.direction_vec);
	if (find_nearest_objects(&shadow_ray, objects, object) == NULL)
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

void	register_hooks(t_window_info *info, t_scene *scene)
{
	mlx_hook(info->win, X_EVENT_KEY_PRESS, 1, &deal_key, scene);
	mlx_hook(info->win, X_EVENT_KEY_EXIT, 1, &close_windows, scene);
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
	mlx_put_image_to_window(info->mlx, info->win, info->img->mlx_img, 0, 0);
	register_hooks(info, scene);
	return (0);
}
