/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:26:14 by ahayashi          #+#    #+#             */
/*   Updated: 2022/05/24 14:16:37 by ahayashi         ###   ########.fr       */
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

	lookfrom = scene->camera->view_point;
	lookat = vec3_add(lookfrom, scene->camera->orientation_vector);
	camera_ray = vec3_normalize(vec3_sub(lookat, lookfrom));
	return (camera_ray);
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
	vec = vec3_add(scene->camera->view_point, camera_ray);
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
			ray.direction_vector = vec3_sub(to_3d(scene, i, j), ray.start_vector);
			if (is_cross(&ray, scene->sphere))
			{
				pixel_put_to_image(info->img, i, j, add_color(calc_diffuse_light(&ray, scene->sphere, scene->light), calc_ambient_light(scene->ambient_lightning)));
			}
			j++;
		}
		i++;
	}
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
			ray.direction_vector = vec3_sub(to_3d(scene, i, j), ray.start_vector);
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
	draw_sphere(info, scene);
//	draw_plane(info, scene);
/*
 *
 * t_object *find_nearest_objects(ray, scene, ignore) {
 * int min_t;
 * t_object *find;
 * while (i) {
 *  is_corss(object);
 * }
 * return find;
 * }
 *
 *
 * while (i)
 * 	while (j)
 * 	 object = find_nearest_objects(i,j);
 * 	 if (object != NULL) {
 * 	 	if (find_nearest_objects(i,j) {
 * 	 		// color = black
 * 	 	}
 * 	 	else
*	 	 	color = cal_diffuse_light(ray, object, light);
 * 	 	image_to_put(color);
 * 	 }
 *
 *
 */

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
