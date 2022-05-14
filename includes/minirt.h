/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: takkatao <takkatao@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 16:29:44 by ahayashi          #+#    #+#             */
/*   Updated: 2022/05/14 16:17:02 by takkatao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include "xlibft.h"
# include "vector3.h"
# include "math.h"

# define H 1001
# define W 1001

typedef struct s_image {
	void	*mlx_img;
	char	*data_addr;
	int		bits_per_pixel;
	int		bytes_per_line;
	int		endian;
	int		width;
	int		height;
}	t_image;

typedef struct s_window_info {
	void		*mlx;
	void		*win;
	t_image		*img;
}	t_window_info;

#endif
