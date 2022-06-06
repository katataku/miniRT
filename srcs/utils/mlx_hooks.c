/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 22:18:19 by takkatao          #+#    #+#             */
/*   Updated: 2022/06/04 22:18:33 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	close_windows(t_scene *scene)
{
	(void)scene;
	exit(0);
}

int	key_pressed(int key_code, t_scene *scene)
{
	if (key_code == KEY_ESC)
		close_windows(scene);
	return (0);
}

int	redraw(void *params)
{
	t_window_info	*info;

	info = (t_window_info *)params;
	mlx_put_image_to_window(info->mlx, info->win, info->img->mlx_img, 0, 0);
	return (0);
}

void	register_hooks(t_window_info *info, t_scene *scene)
{
	mlx_key_hook(info->win, &key_pressed, scene);
	mlx_hook(info->win, DESTROYNOTIFY, STRUCTNOTIFYMASK, \
		&close_windows, scene);
	mlx_hook(info->win, FOCUSIN, FOCUSCHANGEMASK, &redraw, info);
}
