/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:26:14 by ahayashi          #+#    #+#             */
/*   Updated: 2022/05/31 14:54:56 by takkatao         ###   ########.fr       */
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

void	register_hooks(t_window_info *info, t_scene *scene)
{
	mlx_hook(info->win, X_EVENT_KEY_PRESS, 1, &deal_key, scene);
	mlx_hook(info->win, X_EVENT_KEY_EXIT, 1, &close_windows, scene);
}

int	main(int argc, char **argv)
{
	t_window_info	*info;
	t_scene			*scene;

	validate_arg(argc, argv);
	scene = read_file(argv);
	info = init_window_info();
	draw(info, scene);
	register_hooks(info, scene);
	mlx_put_image_to_window(info->mlx, info->win, info->img->mlx_img, 0, 0);
	mlx_loop(info->mlx);
	return (0);
}
