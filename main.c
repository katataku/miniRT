/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahayashi <ahayashi@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:26:14 by ahayashi          #+#    #+#             */
/*   Updated: 2022/04/02 17:31:12 by ahayashi         ###   ########.fr       */
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

int	main(int argc, char **argv, char **env)
{
	void	*mlx;
	void	*win;
	t_image	*img;

	(void)argc;
	(void)argv;
	(void)env;
	mlx = mlx_init();
	win = mlx_new_window(mlx, 1001, 1001, "minirt");
	img = malloc(sizeof(t_image));
	img->mlx_img = mlx_new_image(mlx, 1001, 1001);
	mlx_put_image_to_window(mlx, win, img->mlx_img, 0, 0);
	mlx_loop(mlx);
	return (0);
}

//game->img.mlx_img = mlx_new_image(game->mlx, game->width, game->height);