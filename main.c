/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:26:14 by ahayashi          #+#    #+#             */
/*   Updated: 2022/05/31 14:42:39 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

t_object	*find_nearest_objects(t_ray *ray, t_list *objects, \
									t_object *ignore_object)
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

bool	is_shadow(t_ray *camera_ray, t_object *object, \
					t_light *light, t_list *objects)
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

int	calc_pixel_color(int x, int y, t_scene *sc)
{
	t_object	*object;
	t_vec3		*vec_3d;
	t_ray		ray;
	int			color;

	color = COLOR_BLACK;
	ray.start_vec = sc->camera->point;
	vec_3d = to_screen_vec(sc, x, y);
	ray.direction_vec = vec3_sub(vec_3d, ray.start_vec);
	object = find_nearest_objects(&ray, sc->objects, NULL);
	if (object != NULL && !is_shadow(&ray, object, sc->light, sc->objects))
	{
		color = add_color(color, calc_diffuse_light(&ray, object, sc->light));
		color = add_color(color, calc_ambient_light(sc->ambient_light, object));
	}
	free(vec_3d);
	free(ray.direction_vec);
	return (color);
}

void	draw(t_window_info *info, t_scene *scene)
{
	int	i;
	int	j;
	int	color;

	i = 0;
	while (i < W)
	{
		j = 0;
		while (j < H)
		{
			color = calc_pixel_color(i, j, scene);
			pixel_put_to_image(info->img, i, j, color);
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
