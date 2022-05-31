/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 14:50:18 by takkatao          #+#    #+#             */
/*   Updated: 2022/05/31 14:51:18 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"

static t_object	*find_nearest_objects(t_ray *ray, t_list *objects, \
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

static bool	is_shadow(t_ray *camera_ray, t_object *object, \
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
